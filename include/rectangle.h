#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../include/composant.h"

#define VIDE   0
#define REMPLI 1


/*
 * La structure d'un rectangle.
 */
typedef struct composant* Rectangle;



/*
 * Crée un nouveau rectangle.
 */
Rectangle creer_rectangle(int x, int y, unsigned int largeur, unsigned int hauteur, couleur couleur, int rempli);

/*
 * Dessine un rectangle.
 */
void dessiner_rectangle(const Rectangle a_dessiner);

/*
 * Modifie la largeur d'un rectangle.
 */
void changer_largeur(Rectangle r, unsigned int largeur);

/*
 * Retourne la largeur d'un rectangle.
 */
unsigned int recuperer_largeur(const Rectangle r);

/*
 * Modifie la hauteur d'un rectangle.
 */
void changer_hauteur(Rectangle r, unsigned int hauteur);

/*
 * Retourne la hauteur d'un rectangle.
 */
unsigned int recuperer_hauteur(const Rectangle r);

/*
 * Modifie le remplissage d'un rectangle.
 */
void changer_remplissage(Rectangle r, int remplissage);

/*
 * Retourne le remplissage d'un rectangle.
 */
int recuperer_remplissage(const Rectangle r);

/*
 * Détruit un rectangle.
 */
void detruire_rectangle(Rectangle a_detruire);


#endif
