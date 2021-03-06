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
  Fenetre fenetre;       /* La fenêtre associée. */
  short x;               /* L'abscisse, en pixels. */
  short y;               /* L'ordonnée, en pixels. */
  couleur couleur;       /* La couleur. */
  void * nature;         /* La nature. */
  struct vtable actions; /* Les actions disponibles. */
};



/*
 * Crée un nouveau composant.
 */
Composant creer_composant(int x,           /* L'abscisse, en pixels. */
                          int y,           /* L'ordonnée, en pixels. */
                          couleur couleur) /* La couleur. */
{
  Composant nouveau; /* Le nouveau composant. */


  /* Allocation d'un espace mémoire pour le composant. */
  nouveau = (Composant) malloc(sizeof(struct composant));

  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouveau)
  {
    /* Initialisation du composant. */
    nouveau->fenetre = NULL;
    nouveau->x = (short) x;
    nouveau->y = (short) y;
    nouveau->couleur = couleur;
    nouveau->nature = NULL;
    /* Initialisation de la vtable. */
    nouveau->actions.dessiner = &dessiner_composant;
    nouveau->actions.detruire = &detruire_composant;
  }
  else
  {
    fprintf(stderr, "creer_composant : impossible d'allouer une mémoire suffisante.\n");
  }


  /* Retourne le nouveau composant. */
  return nouveau;
}



/*
 * Modifie la fenêtre à laquelle appartient un composant. Un composant ne peut appartenir
 * qu'à une seule fenêtre.
 */
void changer_fenetre(Fenetre f,   /* La nouvelle fenêtre. */
                     Composant c) /* Le composant concerné. */
{
  /* Le composant ne peut appartenir qu'à une seule fenêtre. */
  if (c->fenetre == NULL)
  {
    /* Modifie la fenêtre à laquelle appartient le composant. */
    c->fenetre = f;
  }
  else
  {
    fprintf(stderr, "changer_fenetre : un composant ne peut ");
    fprintf(stderr, "appartenir qu'à une seule fenêtre.\n");
  }
}



/*
 * Dessine un composant.
 */
void dessiner_composant(const Composant a_dessiner) /* Le composant à dessiner. */
{
  /* Un simple composant ne peut pas être dessiné. */
  fprintf(stderr, "dessiner : impossible de dessiner le composant.\n");
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
 * Modifie l'abscisse d'un composant.
 */
void changer_x(Composant c, /* Le composant concerné. */
               int x)       /* La nouvelle abscisse. */
{
  /* Modifie l'abscisse du composant. */
  c->x = (short) x;

  /* Rafraîchit la fenêtre si nécessaire. */
  if (c->fenetre)
  {
    rafraichir(c->fenetre);
  }
}



/*
 * Retourne l'abscisse d'un composant.
 */
int recuperer_x(const Composant c) /* Le composant concerné. */
{
  /* Retourne l'abscisse du composant. */
  return (int) c->x;
}



/*
 * Modifie l'ordonnée d'un composant.
 */
void changer_y(Composant c, /* Le composant concerné. */
               int y)       /* La nouvelle ordonnée. */
{
  /* Modifie l'ordonnée du composant. */
  c->y = (short) y;

  /* Rafraîchit la fenêtre si nécessaire. */
  if (c->fenetre)
  {
    rafraichir(c->fenetre);
  }
}



/*
 * Retourne l'ordonnée d'un composant.
 */
int recuperer_y(const Composant c) /* Le composant concerné. */
{
  /* Retourne l'ordonnée du composant. */
  return (int) c->y;
}



/*
 * Modifie la couleur d'un composant.
 */
void changer_couleur(Composant c,     /* Le composant concerné. */
                     couleur couleur) /* La nouvelle couleur. */
{
  /* Modifie la couleur du composant. */
  c->couleur = couleur;

  /* Rafraîchit la fenêtre si nécessaire. */
  if (c->fenetre)
  {
    rafraichir(c->fenetre);
  }
}



/*
 * Retourne la couleur d'un composant.
 */
couleur recuperer_couleur(const Composant c) /* Le composant concerné. */
{
  /* Retourne la couleur du composant. */
  return c->couleur;
}



/*
 * Modifie la nature d'un composant. La nature d'un composant est unique.
 */
void changer_nature(Composant c,   /* Le composant concerné. */
                    void * nature) /* La nouvelle nature. */
{
  /* La nature du composant est unique. */
  if (c->nature == NULL)
  {
    /* Modifie la nature du composant. */
    c->nature = nature;
  }
  else
  {
    fprintf(stderr, "changer_nature : la nature d'un composant est unique.\n");
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
void changer_action_dessiner(Composant c,          /* Le composant concerné. */
                             dessinateur dessiner) /* La fonction de dessin. */
{
  /* Modifie la fonction de dessin du composant. */
  c->actions.dessiner = dessiner;
}



/*
 * Modifie le destructeur d'un composant.
 */
void changer_action_detruire(Composant c,          /* Le composant concerné. */
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
