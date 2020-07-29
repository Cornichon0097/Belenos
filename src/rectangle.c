#include <stdlib.h>

#include "../include/rectangle.h"


struct rectangle
{
  unsigned char largeur;
  unsigned char hauteur;
};



/*
 * Crée un nouveau rectangle.
 */
Rectangle creer_rectangle(int x,                /* L'abscisse du rectangle, en pixels. */
                          int y,                /* L'ordonnée du rectangle, en pixels. */
                          unsigned int largeur, /* La largeur du rectangle, en pixels. */
                          unsigned int hauteur, /* La hauteur du rectangle, en pixels. */
                          couleur couleur)      /* La couleur du rectangle. */
{
  Rectangle nouveau = creer_composant(x, y, couleur); /* Le nouveau rectangle. */
  struct rectangle * rectangle = (struct rectangle*) malloc(sizeof(struct rectangle));


  if (rectangle)
  {
    rectangle->largeur = (unsigned char) largeur;
    rectangle->hauteur = (unsigned char) hauteur;
  }
  else
  {
    detruire_composant(nouveau);
    nouveau = NULL;
  }

  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouveau)
  {
    /* Initialisation du rectangle. */
    changer_action_dessin(nouveau, &dessiner_rectangle);
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
  struct rectangle * rectangle = (struct rectangle*) recuperer_nature(a_dessiner);


  XSetForeground(recuperer_affichage(destination),
                 recuperer_contexte_graphique(destination),
                 recuperer_couleur(a_dessiner));
  XDrawRectangle(recuperer_affichage(destination), recuperer_ecran(destination),
                 recuperer_contexte_graphique(destination),
                 recuperer_x(a_dessiner), recuperer_y(a_dessiner),
                 (unsigned int) rectangle->largeur, (unsigned int) rectangle->hauteur);
  XFlush(recuperer_affichage(destination));
}



/*
 * Détruit un rectangle.
 */
void detruire_rectangle(Rectangle a_detruire) /* Le rectangle à détruire. */
{
  detruire_composant(a_detruire);
}
