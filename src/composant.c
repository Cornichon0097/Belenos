#include <stdlib.h>
#include <stdio.h>

#include "../include/composant.h"


/*
 * La structure d'un composant.
 * Le composant est destiné à un usage graphique. Il est généralement dessiné et affiché
 * dans la fenêtre à laquelle il appartient. Sa nature peut varier selon le besion.
 */
struct composant
{
  signed char x;         /* L'abscisse, en pixels. */
  signed char y;         /* L'ordonnée, en pixels. */
  couleur couleur;       /* La couleur. */
  void * nature;         /* La nature. */
  struct vtable actions; /* Les actions disponibles. */
};



/*
 * Crée un nouveau composant.
 */
Composant creer_composant(int x,           /* L'abscisse du composant, en pixels. */
                          int y,           /* L'ordonnée du composant, en pixels. */
                          couleur couleur) /* La couleur du composant. */
{
  Composant nouveau = (Composant) malloc(sizeof(struct composant)); /* Le nouveau composant. */


  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouveau)
  {
    /* Initialisation du composant. */
    nouveau->x = (signed char) x;
    nouveau->y = (signed char) y;
    nouveau->couleur = couleur;
    nouveau->nature = NULL;
    nouveau->actions.dessiner = &dessiner_composant;
    nouveau->actions.detruire = &detruire_composant;
  }


  /* Retourne le nouveau composant. */
  return nouveau;
}



/*
 * Dessine un composant. Un simple composant ne peut pas être dessiné.
 */
void dessiner_composant(const Fenetre destination,  /* La fenêtre destination. */
                        const Composant a_dessiner) /* Le composant à dessiner. */
{
  fprintf(stderr, "dessiner : un simple composant ne peut pas être dessiné.\n");
}



/*
 * Modifie l'abscisse d'un composant.
 */
void changer_x(Composant c, /* Le composant concerné. */
               int x)       /* La nouvelle abscisse. */
{
  c->x = (signed char) x;
}



/*
 * Retourne l'abscisse d'un composant.
 */
int recuperer_x(const Composant c) /* Le composant concerné. */
{
  return (int) c->x;
}



/*
 * Modifie l'ordonnée d'un composant.
 */
void changer_y(Composant c, /* Le composant concerné. */
               int y)       /* La nouvelle ordonnée. */
{
  c->y = (signed char) y;
}



/*
 * Retourne l'ordonnée d'un composant.
 */
int recuperer_y(const Composant c) /* Le composant concerné. */
{
  return (int) c->y;
}



/*
 * Modifie la couleur d'un composant.
 */
void changer_couleur(Composant c,     /* Le composant concerné. */
                     couleur couleur) /* La nouvelle couleur du composant. */
{
  c->couleur = couleur;
}



/*
 * Retourne la couleur d'un composant.
 */
couleur recuperer_couleur(const Composant c) /* Le composant concerné. */
{
  return c->couleur;
}



/*
 * Modifie la fonction de dessin d'un composant.
 */
void changer_action_dessin(Composant c,                                      /* Le composant concerné. */
                           void (*dessiner)(const Fenetre, const Composant)) /* La fonction de dessin. */
{
  c->actions.dessiner = dessiner;
}



/*
 * Modifie le destructeur d'un composant.
 */
void changer_action_detruire(Composant c,                       /* Le composant concerné. */
                             void (*detruire)(const Composant)) /* Le destructeur. */
{
  c->actions.detruire = detruire;
}



/*
 * Retourne la vtable d'un composant.
 */
struct vtable action(const Composant c) /* Le composant concerné. */
{
  return c->actions;
}



/*
 * Détruit un composant.
 */
void detruire_composant(Composant a_detruire) /* Le composant à détruire. */
{
  /* La mémoire dédiée au composant est libérée. */
  free(a_detruire);
}
