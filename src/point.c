#include <stdio.h>

#include "../include/point.h"



/*
 * Crée un nouveau point.
 */
Point creer_point(int x,           /* L'abscisse, en pixels. */
                  int y,           /* L'ordonnée, en pixels. */
                  Couleur couleur) /* La couleur. */
{
  Point nouveau = creer_composant(x, y, couleur); /* Le nouveau point. */


  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouveau)
  {
    /* Initialisation du point. */
    changer_action_dessiner(nouveau, &dessiner_point);
    changer_action_detruire(nouveau, &detruire_point);
  }


  /* Retourne le nouveau point. */
  return nouveau;
}



/*
 * Dessine un point.
 */
void dessiner_point(const Point a_dessiner) /* Le point à dessiner. */
{
  XSetForeground(recuperer_affichage(recuperer_fenetre(a_dessiner)),
                 recuperer_contexte_graphique(recuperer_fenetre(a_dessiner)),
                 recuperer_couleur_hex(recuperer_couleur(a_dessiner)));
  /* Dessine le point. */
  XDrawPoint(recuperer_affichage(recuperer_fenetre(a_dessiner)), recuperer_ecran(recuperer_fenetre(a_dessiner)),
             recuperer_contexte_graphique(recuperer_fenetre(a_dessiner)),
             recuperer_x(a_dessiner), recuperer_y(a_dessiner));
  XFlush(recuperer_affichage(recuperer_fenetre(a_dessiner)));
}



/*
 * Détruit un point.
 */
void detruire_point(Point a_detruire) /* Le point à détruire. */
{
  /* La mémoire dédiée au point est libérée. */
  detruire_composant(a_detruire);
}
