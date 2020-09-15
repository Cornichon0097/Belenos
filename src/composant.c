#include <stdlib.h>
#include <stdio.h>

#include "../include/composant.h"


/*
 * La structure d'un composant.
 * Le composant est destiné à un usage graphique. Il est généralement dessiné et affiché
 * dans la fenêtre à laquelle il appartient. Sa nature peut varier selon les besions.
 */
struct composant
{
  Fenetre       fenetre;      /* La fenêtre associée. */
  Window        ecran;        /*  */ /* Encore en phase de test. */
  couleur       premier_plan; /* La couleur du premier plan. */
  couleur       arriere_plan; /* La couleur de l'arrière plan. */
  void *        nature;       /* La nature. Elle définit le composant. */
  struct vtable actions;      /* Les actions disponibles. */
};



/*
 * Crée un nouveau composant.
 */
Composant creer_composant(void)
{
  Composant nouveau; /* Le nouveau composant. */


  /* Allocation d'un espace mémoire pour le composant. */
  nouveau = (Composant) malloc(sizeof(struct composant));

  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouveau)
  {
    /* Initialisation du composant. */
    nouveau->fenetre      = NULL;
    nouveau->ecran        = 0;
    nouveau->premier_plan = NOIR;
    nouveau->arriere_plan = BLANC;
    nouveau->nature       = NULL;
    /* Initialisation de la vtable. */
    nouveau->actions.dessiner = &dessiner_composant;
    nouveau->actions.detruire = &detruire_composant;
  }
  else
  {
    fprintf(stderr, "creer_composant() : impossible d'allouer ");
    fprintf(stderr, "une zone mémoire suffisante.\n");
  }


  /* Retourne le nouveau composant. */
  return nouveau;
}



/*
 * Dessine un composant.
 */
void dessiner_composant(const Composant a_dessiner) /* Le composant à dessiner. */
{
  XWindowAttributes attributs;


  if (a_dessiner->fenetre == NULL)
  {
    fprintf(stderr, "dessiner_composant() : le composant ");
    fprintf(stderr, "n'appartient pas à une fenêtre.\n");
    return;
  }

  XGetWindowAttributes(recuperer_affichage(a_dessiner->fenetre),
                        a_dessiner->ecran, &attributs);

  XSetForeground(recuperer_affichage(a_dessiner->fenetre),
                 recuperer_contexte_graphique(a_dessiner->fenetre),
                 a_dessiner->arriere_plan);
  XFillRectangle(recuperer_affichage(a_dessiner->fenetre), a_dessiner->ecran,
                 recuperer_contexte_graphique(a_dessiner->fenetre),
                 0, 0, attributs.width, attributs.height);
  XFlush(recuperer_affichage(a_dessiner->fenetre));
}



/*
 * Modifie la fenêtre à laquelle appartient un composant. Un composant ne peut appartenir
 * qu'à une seule fenêtre.
 */
void changer_fenetre(Composant c, /* Le composant concerné. */
                     Fenetre   f) /* La nouvelle fenêtre. */
{
  /* Le composant ne peut appartenir qu'à une seule fenêtre. */
  if (c->fenetre == NULL)
  {
    /* Modifie la fenêtre à laquelle appartient le composant. */
    c->fenetre = f;
  }
  else
  {
    fprintf(stderr, "changer_fenetre() : un composant ne peut ");
    fprintf(stderr, "appartenir qu'à une seule fenêtre.\n");
  }
}



/*
 * Retourne la fenêtre à laquelle appartient un composant.
 */
Fenetre recuperer_fenetre(const Composant c) /* Le composant concerné. */
{
  /* Retourne la fenêtre à laquelle appartient le composant. */
  return c->fenetre;
}



/*
 * Modifie l'écran auquel appartient un composant. Un composant ne peut appartenir
 * qu'à un seul écran.
 */
void changer_ecran(Composant c, /* Le composant concerné. */
                   Window    w) /* Le nouvel écran. */
{
  /* Le composant ne peut appartenir qu'a un seul écran. */
  if (c->ecran == 0)
  {
    /* Modifie l'écran auquel appartient le composant. */
    c->ecran = w;
  }
  else
  {
    fprintf(stderr, "changer_ecran() : un composant ne peut ");
    fprintf(stderr, "appartenir qu'à un seul écran.\n");
  }
}



/*
 * Retourne l'écran auquel appartient un composant.
 */
Window recuperer_ecran(const Composant c) /* Le composant concerné. */
{
  /* Retourne l'écran auquel appartient le composant. */
  return c->ecran;
}



/*
 * Modifie la couleur du premier plan d'un composant.
 */
void changer_premier_plan(Composant c,       /* Le composant concerné. */
                          couleur   couleur) /* La nouvelle couleur. */
{
  /* Modifie la couleur du premier plan du composant. */
  c->premier_plan = couleur;

  /* Rafraîchit la fenêtre si nécessaire. */
  if (c->fenetre)
  {
    rafraichir(c->fenetre);
  }
}



/*
 * Retourne la couleur du premier plan d'un composant.
 */
couleur recuperer_premier_plan(const Composant c) /* Le composant concerné. */
{
  /* Retourne la couleur du premier plan du composant. */
  return c->premier_plan;
}



/*
 * Modifie la couleur de l'arrière plan d'un composant.
 */
void changer_arriere_plan(Composant c,       /* Le composant concerné. */
                          couleur   couleur) /* La nouvelle couleur. */
{
  /* Modifie la couleur de l'arrière plan du composant. */
  c->arriere_plan = couleur;

  /* Rafraîchit la fenêtre si nécessaire. */
  if (c->fenetre)
  {
    rafraichir(c->fenetre);
  }
}



/*
 * Retourne la couleur de l'arrière plan d'un composant.
 */
couleur recuperer_arriere_plan(const Composant c) /* Le composant concerné. */
{
  /* Retourne la couleur de l'arrière plan du composant. */
  return c->arriere_plan;
}



/*
 * Modifie la nature d'un composant. La nature d'un composant est unique.
 */
void changer_nature(Composant c,      /* Le composant concerné. */
                    void *    nature) /* La nouvelle nature. */
{
  /* La nature du composant est unique. */
  if (c->nature == NULL)
  {
    /* Modifie la nature du composant. */
    c->nature = nature;
  }
  else
  {
    fprintf(stderr, "changer_nature() : la nature d'un composant est unique.\n");
  }
}



/*
 * Retourne la nature d'un composant.
 */
void * recuperer_nature(const Composant c) /* Le composant concerné. */
{
  /* Retourne la nature du composant. */
  return c->nature;
}



/*
 * Modifie la fonction de dessin d'un composant.
 */
void changer_action_dessiner(Composant   c,        /* Le composant concerné. */
                             dessinateur dessiner) /* La fonction de dessin. */
{
  /* Modifie la fonction de dessin du composant. */
  c->actions.dessiner = dessiner;
}



/*
 * Modifie le destructeur d'un composant.
 */
void changer_action_detruire(Composant   c,        /* Le composant concerné. */
                             destructeur detruire) /* Le destructeur. */
{
  /* Modifie le destructeur du composant. */
  c->actions.detruire = detruire;
}



/*
 * Retourne les actions disponibles pour un composant.
 */
struct vtable action(const Composant c) /* Le composant concerné. */
{
  /* Retourne les actions disponibles pour le composant. */
  return c->actions;
}



/*
 * Détruit un composant.
 */
void detruire_composant(Composant a_detruire) /* Le composant à détruire. */
{
  /* La mémoire dédiée au composant est libérée. */
  free(a_detruire);
}
