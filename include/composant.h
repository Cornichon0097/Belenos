#ifndef COMPOSANT_H
#define COMPOSANT_H

#include "../include/couleur.h"


/*
 * La structure d'un composant.
 */
typedef struct composant* Composant;


#include "../include/fenetre.h"


/*
 * La structure de la vtable d'un composant.
 */
struct vtable
{
  void (*dessiner)(const Fenetre, const Composant); /* La fonction de dessin.  */
  void (*detruire)(Composant);                      /* Le destructeur. */
};



/*
 * Crée un nouveau composant.
 */
Composant creer_composant(int x, int y, couleur c);

/*
 * Dessine un composant. Un simple composant ne peut pas être dessiné.
 */
void dessiner_composant(const Fenetre destination, const Composant a_dessiner);

/*
 * Détruit un composant.
 */
void detruire_composant(Composant a_detruire);


#endif
