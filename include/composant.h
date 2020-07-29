#ifndef COMPOSANT_H
#define COMPOSANT_H

#include "../include/couleur.h"


/*
 * La structure d'un composant.
 */
typedef struct composant* Composant;


#include "../include/fenetre.h"


/*
 * La structure d'une vtable d'un composant.
 * La vtable répertorie les fonctions susceptibles de changer selon le composant.
 */
struct vtable
{
  void (*dessiner)(const Fenetre, const Composant); /* La fonction de dessin. */
  void (*detruire)(Composant);                      /* Le destructeur. */
};



/*
 * Crée un nouveau composant.
 */
Composant creer_composant(int x, int y, couleur couleur);

/*
 * Dessine un composant. Un simple composant ne peut pas être dessiné.
 */
void dessiner_composant(const Fenetre destination, const Composant a_dessiner);

/*
 * Modifie l'abscisse d'un composant.
 */
void changer_x(Composant c, int x);

/*
 * Retourne l'abscisse d'un composant.
 */
int recuperer_x(const Composant c);

/*
 * Modifie l'ordonnée d'un composant.
 */
void changer_y(Composant c, int y);

/*
 * Retourne l'ordonnée d'un composant.
 */
int recuperer_y(const Composant c);

/*
 * Modifie la couleur d'un composant.
 */
void changer_couleur(Composant c, couleur couleur);

/*
 * Retourne la couleur d'un composant.
 */
couleur recuperer_couleur(const Composant c);

/*
 * Modifie la fonction de dessin d'un composant.
 */
void changer_action_dessin(Composant c, void (*dessiner)(const Fenetre, const Composant));

/*
 * Modifie le destructeur d'un composant.
 */
void changer_action_detruire(Composant c, void (*detruire)(const Composant));

/*
 * Retourne la vtable d'un composant.
 */
struct vtable action(const Composant c);

/*
 * Détruit un composant.
 */
void detruire_composant(Composant a_detruire);


#endif
