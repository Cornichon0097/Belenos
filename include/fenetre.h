#ifndef FENETRE_H
#define FENETRE_H

#include <X11/Xlib.h>


/* La structure d'une fenêtre. */
typedef struct fenetre* Fenetre;



/*
 * Crée une nouvelle fenêtre.
 */
Fenetre creer_fenetre(int x, int y, unsigned int largeur, unsigned int hauteur);

/*
 * Affiche une fenêtre à l'écran.
 */
void afficher_fenetre(Fenetre f);

/*
 * Retourne l'affichage d'une fenêtre.
 */
Display * recuperer_affichage(const Fenetre f);

/*
 * Retourne l'écran actif d'une fenêtre.
 */
Window recuperer_ecran(const Fenetre f);

/*
 * Retourne le contexte graphique d'une fenêtre.
 */
GC recuperer_contexte_graphique(const Fenetre f);

/*
 * Retourne si une fenêtre est ouverte.
 */
int est_ouverte(const Fenetre f);

/*
 * Ajoute un composant à une fenêtre.
 */
void ajouter(const Fenetre f, void * a_ajouter);

/*
 * Détruit une fenêtre.
 */
void detruire_fenetre(Fenetre a_detruire);


#endif
