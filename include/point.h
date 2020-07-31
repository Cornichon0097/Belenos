#ifndef POINT_H
#define POINT_H

#include "../include/composant.h"


/*
 * La structure d'un point.
 * La structure du point est la même que pour le composant : c'est un cas unique.
 */
typedef struct composant* Point;



/*
 * Crée un nouveau point.
 */
Point creer_point(int x, int y, Couleur couleur);

/*
 * Dessine un point.
 */
void dessiner_point(const Fenetre destination, const Point a_dessiner);

/*
 * Détruit un point.
 */
void detruire_point(Point a_detruire);


#endif
