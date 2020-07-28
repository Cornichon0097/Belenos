#ifndef COMPOSANT_H
#define COMPOSANT_H

#include "../include/couleur.h"
#include "../include/fenetre.h"


typedef struct composant* Composant;



Composant creer_composant(Fenetre f, int x, int y);


#endif
