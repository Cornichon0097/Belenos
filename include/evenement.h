#ifndef EVENEMENT
#define EVENEMENT

#include<X11/keysym.h>

#include "../include/fenetre.h"



/*
 * Affiche une fenêtre à l'écran.
 */
void afficher_fenetre(Fenetre f);

int est_ouverte(const Fenetre f);

KeySym touche_pressee(const Fenetre f);

KeySym touche_relachee(const Fenetre f);

unsigned int bouton_presse(const Fenetre f);

unsigned int bouton_relache(const Fenetre f);


#endif
