#include <stdio.h>

#include "../include/point.h"



/*
 * Crée un nouveau point.
 */
Point creer_point(int x,           /* L'abscisse du point, en pixels. */
                  int y,           /* L'ordonnée du point, en pixels. */
                  couleur couleur) /* La couleur du point. */
{
  Point nouveau = creer_composant(x, y, couleur); /* Le nouveau point. */


  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouveau)
  {
    /* Initialisation du point. */
    changer_action_dessin(nouveau, &dessiner_point);
    changer_action_detruire(nouveau, &detruire_point);
  }


  /* Retourne le nouveau point. */
  return nouveau;
}



/*
 * Dessine un point.
 */
void dessiner_point(const Fenetre destination, /* La fenêtre destination. */
                    const Point a_dessiner)    /* Le point à dessiner. */
{
  XSetForeground(recuperer_affichage(destination),
                 recuperer_contexte_graphique(destination),
                 recuperer_couleur(a_dessiner));
  XDrawPoint(recuperer_affichage(destination), recuperer_ecran(destination),
             recuperer_contexte_graphique(destination),
             recuperer_x(a_dessiner), recuperer_y(a_dessiner));
  XFlush(recuperer_affichage(destination));
}



/*
 * Détruit un point.
 */
void detruire_point(Point a_detruire) /* Le point à détruire. */
{
  detruire_composant(a_detruire);
}
