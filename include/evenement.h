#ifndef EVENEMENT
#define EVENEMENT

#include<X11/keysym.h>

#include "../include/fenetre.h"



KeySym touche_pressee(const Fenetre f);

KeySym touche_relachee(const Fenetre f);


#endif
