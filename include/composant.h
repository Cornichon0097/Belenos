#ifndef COMPOSANT_H
#define COMPOSANT_H

#include "../include/couleur.h"


typedef struct composant* Composant;


#include "../include/fenetre.h"



Composant creer_composant(int x, int y, couleur c);

void dessiner_composant(const Fenetre destination, const Composant a_dessiner);

void detruire_composant(Composant a_detruire);


#endif
