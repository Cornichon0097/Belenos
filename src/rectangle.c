#include <stdlib.h>
#include <stdio.h>

#include "../include/rectangle.h"


/*
 * La structure d'un rectangle.
 * Le rectangle est un composant doté d'une largeur et d'une hauteur.
 */
struct rectangle
{
  unsigned short largeur;    /* La largeur. */
  unsigned short hauteur;    /* La hauteur. */
  unsigned char remplissage; /* Si le rectangle est rempli. */
};



/*
 * Crée un nouveau rectangle.
 */
Rectangle creer_rectangle(int x,                /* L'abscisse, en pixels. */
                          int y,                /* L'ordonnée, en pixels. */
                          unsigned int largeur, /* La largeur, en pixels. */
                          unsigned int hauteur, /* La hauteur, en pixels. */
                          couleur couleur,      /* La couleur. */
                          int remplissage)      /* Si le rectangle est rempli. */
{
  /* Le nouveau rectangle : */
  Rectangle nouveau = creer_composant(x, y, couleur);
  struct rectangle * rectangle = (struct rectangle*) malloc(sizeof(struct rectangle));


  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (rectangle)
  {
    /* Initialisation du rectangle. */
    rectangle->largeur = (unsigned short) largeur;
    rectangle->hauteur = (unsigned short) hauteur;
    rectangle->remplissage = (unsigned char) remplissage;
  }
  /* Sinon, la création du rectangle est abandonnée. */
  else
  {
    fprintf(stderr, "creer_rectangle : impossible d'allouer une mémoire suffisante.\n");
    detruire_composant(nouveau);
    nouveau = NULL;
  }

  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouveau)
  {
    /* Initialisation du rectangle. */
    changer_action_dessiner(nouveau, &dessiner_rectangle);
    changer_action_detruire(nouveau, &detruire_rectangle);
    changer_nature(nouveau, rectangle);
  }


  /* Retourne le nouveau rectangle. */
  return nouveau;
}



/*
 * Dessine un rectangle.
 */
void dessiner_rectangle(const Rectangle a_dessiner) /* Le rectangle à dessiner. */
{
  /* Les propriétés du composant qui en font un rectangle : */
  struct rectangle * rectangle = (struct rectangle*) recuperer_nature(a_dessiner);


  XSetForeground(recuperer_affichage(recuperer_fenetre(a_dessiner)),
                 recuperer_contexte_graphique(recuperer_fenetre(a_dessiner)),
                 recuperer_couleur(a_dessiner));

  /* Choisit la fonction adaptée pour dessiner le rectangle. */
  if (rectangle->remplissage)
  {
    XFillRectangle(recuperer_affichage(recuperer_fenetre(a_dessiner)),
                   recuperer_ecran(recuperer_fenetre(a_dessiner)),
                   recuperer_contexte_graphique(recuperer_fenetre(a_dessiner)),
                   recuperer_x(a_dessiner), recuperer_y(a_dessiner),
                   (unsigned int) rectangle->largeur, (unsigned int) rectangle->hauteur);
  }
  else
  {
    XDrawRectangle(recuperer_affichage(recuperer_fenetre(a_dessiner)),
                   recuperer_ecran(recuperer_fenetre(a_dessiner)),
                   recuperer_contexte_graphique(recuperer_fenetre(a_dessiner)),
                   recuperer_x(a_dessiner), recuperer_y(a_dessiner),
                   (unsigned int) rectangle->largeur, (unsigned int) rectangle->hauteur);
  }

  XFlush(recuperer_affichage(recuperer_fenetre(a_dessiner)));
}



/*
 * Modifie la largeur d'un rectangle.
 */
void changer_largeur(Rectangle r,          /* Le rectangle concerné. */
                     unsigned int largeur) /* La nouvelle largeur. */
{
  /* Les propriétés du composant qui en font un rectangle : */
  struct rectangle * rectangle = (struct rectangle*) recuperer_nature(r);


  /* Modifie la largeur du rectangle. */
  rectangle->largeur = (unsigned short) largeur;

  /* Rafraîchit la fenêtre si nécessaire. */
  if (recuperer_fenetre(r))
  {
    rafraichir(recuperer_fenetre(r));
  }
}



/*
 * Retourne la largeur d'un rectangle.
 */
unsigned int recuperer_largeur(const Rectangle r) /* Le rectangle concerné. */
{
  /* Les propriétés du composant qui en font un rectangle : */
  struct rectangle * rectangle = (struct rectangle*) recuperer_nature(r);


  /* Retourne la largeur du rectangle. */
  return (unsigned int) rectangle->largeur;
}



/*
 * Modifie la hauteur d'un rectangle.
 */
void changer_hauteur(Rectangle r,          /* Le rectangle concerné. */
                     unsigned int hauteur) /* La nouvelle hauteur. */
{
  /* Les propriétés du composant qui en font un rectangle : */
  struct rectangle * rectangle = (struct rectangle*) recuperer_nature(r);


  /* Modifie la hauteur du rectangle. */
  rectangle->hauteur = (unsigned short) hauteur;

  /* Rafraîchit la fenêtre si nécessaire. */
  if (recuperer_fenetre(r))
  {
    rafraichir(recuperer_fenetre(r));
  }
}



/*
 * Retourne la hauteur d'un rectangle.
 */
unsigned int recuperer_hauteur(const Rectangle r) /* Le rectangle concerné. */
{
  /* Les propriétés du composant qui en font un rectangle : */
  struct rectangle * rectangle = (struct rectangle*) recuperer_nature(r);


  /* Retourne la hauteur du rectangle. */
  return (unsigned int) rectangle->hauteur;
}



/*
 * Modifie le remplissage d'un rectangle.
 */
void changer_remplissage(Rectangle r,     /* Le rectangle concerné. */
                         int remplissage) /* Si le rectangle est rempli. */
{
  /* Les propriétés du composant qui en font un rectangle : */
  struct rectangle * rectangle = (struct rectangle*) recuperer_nature(r);


  /* Modifie le remplissage du rectangle. */
  rectangle->remplissage = (unsigned char) remplissage;

  /* Rafraîchit la fenêtre si nécessaire. */
  if (recuperer_fenetre(r))
  {
    rafraichir(recuperer_fenetre(r));
  }
}



/*
 * Retourne le remplissage d'un rectangle.
 */
int recuperer_remplissage(const Rectangle r) /* Le rectangle concerné. */
{
  /* Les propriétés du composant qui en font un rectangle : */
  struct rectangle * rectangle = (struct rectangle*) recuperer_nature(r);


  /* Retourne le remplissage du rectangle. */
  return (int) rectangle->remplissage;
}



/*
 * Détruit un rectangle.
 */
void detruire_rectangle(Rectangle a_detruire) /* Le rectangle à détruire. */
{
  /* La mémoire dédiée au rectangle est libérée. */
  free(recuperer_nature(a_detruire));
  detruire_composant(a_detruire);
}
