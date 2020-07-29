#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../include/composant.h"


/*
 * La structure d'un rectangle.
 */
typedef struct composant* Rectangle;



/*
 * Crée un nouveau rectangle.
 */
Rectangle creer_rectangle(int x, int y, unsigned int largeur, unsigned int hauteur, couleur couleur);

/*
 * Dessine un rectangle.
 */
void dessiner_rectangle(const Fenetre destination, const Rectangle a_dessiner);

/*
 * Détruit un rectangle.
 */
void detruire_rectangle(Rectangle a_detruire);


#endif
