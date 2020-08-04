#include <stdlib.h>

#include "../include/rectangle.h"


/*
 * La structure d'un rectangle.
 * Le rectangle est un composant doté d'une largeur et d'une hauteur.
 */
struct rectangle
{
  unsigned char largeur; /* La largeur. */
  unsigned char hauteur; /* La hauteur. */
  unsigned char rempli;  /* Si le rectangle est rempli. */
};



/*
 * Crée un nouveau rectangle.
 */
Rectangle creer_rectangle(int x,                /* L'abscisse, en pixels. */
                          int y,                /* L'ordonnée, en pixels. */
                          unsigned int largeur, /* La largeur, en pixels. */
                          unsigned int hauteur, /* La hauteur, en pixels. */
                          Couleur couleur,      /* La couleur. */
                          int rempli)           /* Si le rectangle est rempli. */
{
  /* Le nouveau rectangle : */
  Rectangle nouveau = creer_composant(x, y, couleur);
  struct rectangle * rectangle = (struct rectangle*) malloc(sizeof(struct rectangle));


  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (rectangle)
  {
    /* Initialisation du rectangle. */
    rectangle->largeur = (unsigned char) largeur;
    rectangle->hauteur = (unsigned char) hauteur;
    rectangle->rempli = (unsigned char) rempli;
  }
  /* Sinon, la création du rectangle est abandonnée. */
  else
  {
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
void dessiner_rectangle(const Fenetre destination,  /* La fenêtre destination. */
                        const Rectangle a_dessiner) /* Le rectangle à dessiner. */
{
  /* Les propriétés du composant qui en font un rectangle : */
  struct rectangle * rectangle = (struct rectangle*) recuperer_nature(a_dessiner);


  XSetForeground(recuperer_affichage(destination),
                 recuperer_contexte_graphique(destination),
                 recuperer_couleur_hex(recuperer_couleur(a_dessiner)));

  /* Choisit la fonction adaptée pour dessiner le rectangle. */
  if (rectangle->rempli)
  {
    XFillRectangle(recuperer_affichage(destination), recuperer_ecran(destination),
                   recuperer_contexte_graphique(destination),
                   recuperer_x(a_dessiner), recuperer_y(a_dessiner),
                   (unsigned int) rectangle->largeur, (unsigned int) rectangle->hauteur);
  }
  else
  {
    XDrawRectangle(recuperer_affichage(destination), recuperer_ecran(destination),
                   recuperer_contexte_graphique(destination),
                   recuperer_x(a_dessiner), recuperer_y(a_dessiner),
                   (unsigned int) rectangle->largeur, (unsigned int) rectangle->hauteur);
  }

  XFlush(recuperer_affichage(destination));
}



/*
 * Détruit un rectangle.
 */
void detruire_rectangle(Rectangle a_detruire) /* Le rectangle à détruire. */
{
  /* La mémoire dédiée au rectangle est libérée. */
  free((struct rectangle*) recuperer_nature(a_detruire));
  detruire_composant(a_detruire);
}
