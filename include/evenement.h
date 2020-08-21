#ifndef EVENEMENT
#define EVENEMENT

#include<X11/keysym.h>

#include "../include/fenetre.h"

/* Les boutons principaux de la souris. */
#define VIDE           0
#define CLIQUE_GAUCHE  1
#define CLIQUE_MOLETTE 2
#define CLIQUE_DROITE  3



/*
 * Retourne si une fenêtre est ouverte.
 */
int est_ouverte(const Fenetre f);

/*
 * Retourne la touche du clavier pressée (si touche de clavier pressée il y a).
 */
KeySym touche_pressee(const Fenetre f);

/*
 * Retourne la touche du clavier relâchée (si touche de clavier relâchée il y a).
 */
KeySym touche_relachee(const Fenetre f);

/*
 * Récupère la position de la souris dans la fenêtre.
 */
void position_souris(const Fenetre f, int * x, int * y);

/*
 * Retourne le bouton de la souris pressé (si bouton de souris pressé il y a).
 */
unsigned int bouton_presse(const Fenetre f);

/*
 * Retourne le bouton de la souris relâché (si bouton de souris relâché il y a).
 */
unsigned int bouton_relache(const Fenetre f);


#endif
