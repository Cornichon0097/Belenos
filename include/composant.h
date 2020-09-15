#ifndef COMPOSANT_H
#define COMPOSANT_H

#include "../include/couleur.h"


/*
 * La structure d'un composant.
 */
typedef struct composant* Composant;


#include "../include/fenetre.h"


/*
 * La définition de la fonction de dessin pour un composant.
 */
typedef void (*dessinateur)(const Composant);

/*
* La définition du destructeur pour un composant.
 */
typedef void (*destructeur)(Composant);


/*
 * La structure d'une vtable d'un composant.
 * La vtable répertorie les fonctions susceptibles de changer selon le composant.
 */
struct vtable
{
  dessinateur dessiner; /* La fonction de dessin. */
  destructeur detruire; /* Le destructeur. */
};



/*
 * Crée un nouveau composant.
 */
Composant creer_composant(void);

/*
 * Dessine un composant.
 */
void dessiner_composant(const Composant a_dessiner);

/*
 * Modifie la fenêtre à laquelle appartient un composant. Un composant ne peut appartenir
 * qu'à une seule fenêtre.
 */
void changer_fenetre(Composant c, Fenetre f);

/*
 * Retourne la fenêtre à laquelle appartient un composant.
 */
Fenetre recuperer_fenetre(const Composant c);

/*
 * Modifie l'écran auquel appartient un composant. Un composant ne peut appartenir
 * qu'à un seul écran.
 */
void changer_ecran(Composant c, Window w);

/*
 * Retourne l'écran auquel appartient un composant.
 */
Window recuperer_ecran(const Composant c);

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
 * Modifie la couleur du premier plan d'un composant.
 */
void changer_premier_plan(Composant c, couleur couleur);

/*
 * Retourne la couleur du premier plan d'un composant.
 */
couleur recuperer_premier_plan(const Composant c);

/*
 * Modifie la couleur de l'arrière plan d'un composant.
 */
void changer_arriere_plan(Composant c, couleur couleur);

/*
 * Retourne la couleur de l'arrière plan d'un composant.
 */
couleur recuperer_arriere_plan(const Composant c);

/*
* Modifie la nature d'un composant. La nature d'un composant est unique.
 */
void changer_nature(Composant c, void * nature);

/*
 * Retourne la nature d'un composant.
 */
void * recuperer_nature(const Composant c);

/*
 * Modifie la fonction de dessin d'un composant.
 */
void changer_action_dessiner(Composant c, dessinateur dessiner);

/*
 * Modifie le destructeur d'un composant.
 */
void changer_action_detruire(Composant c, destructeur detruire);

/*
* Retourne les actions disponibles pour un composant.
 */
struct vtable action(const Composant c);

/*
 * Détruit un composant.
 */
void detruire_composant(Composant a_detruire);


#endif
