#ifndef EVENEMENT
#define EVENEMENT

#include<X11/keysym.h>

#include "../include/fenetre.h"



int est_ouverte(const Fenetre f);

KeySym touche_pressee(const Fenetre f);

KeySym touche_relachee(const Fenetre f);


#endif
