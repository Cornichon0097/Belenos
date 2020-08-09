#ifndef FENETRE_H
#define FENETRE_H

#include <X11/Xlib.h>


/*
 * La structure d'une fenêtre.
 */
typedef struct fenetre* Fenetre;


#include "../include/composant.h"



/*
 * Crée une nouvelle fenêtre.
 */
Fenetre creer_fenetre(int x, int y, int largeur, int hauteur);

/*
 * Retourne l'affichage d'une fenêtre.
 */
Display * recuperer_affichage(const Fenetre f);

/*
 * Modifie l'écran actif d'une fenêtre.
 */
void changer_ecran(Fenetre f, int ecran_actif);

/*
 * Retourne l'écran actif d'une fenêtre.
 */
Window recuperer_ecran(const Fenetre f);

/*
 * Retourne le contexte graphique d'une fenêtre.
 */
GC recuperer_contexte_graphique(const Fenetre f);

Atom fermeture(const Fenetre f);

void rafraichir(const Fenetre a_rafraichir);

/*
 * Ajoute un composant à une fenêtre. Cette action a pour effet de dessiner le composant
 * ajouté dans la fenêtre destination, sur l'écran actif uniquement.
 */
void ajouter(const Fenetre f, Composant a_ajouter); /* ! Pas adaptée aux écrans ! */

void position_souris(const Fenetre f, int * x, int * y);

/*
 * Détruit une fenêtre.
 */
void detruire_fenetre(Fenetre a_detruire);


#endif
