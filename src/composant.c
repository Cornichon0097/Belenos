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
  signed char x;   /* L'abscisse, en pixels. */
  signed char y;   /* L'ordonnée, en pixels. */
  couleur couleur; /* La couleur. */
  /* D'autres enregistrements sont à prévoir. */
};



/*
 * Crée un nouveau composant.
 */
Composant creer_composant(int x,     /* L'abscisse du composant, en pixels. */
                          int y,     /* L'ordonnée du composant, en pixels. */
                          couleur c) /* La couleur du composant. */
{
  Composant nouveau /* Le nouveau composant. */
    = (Composant) malloc(sizeof(struct composant));


  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouveau)
  {
    /* Initialisation du composant. */
    nouveau->x = (signed char) x;
    nouveau->y = (signed char) y;
    nouveau->couleur = c;
  }


  /* Retourne le noueau composant. */
  return nouveau;
}



/*
 * Dessine un composant. Un simple composant ne peut pas être dessiné.
 */
void dessiner_composant(const Fenetre destination,  /* La fenêtre destination. */
                        const Composant a_dessiner) /* Le composant à dessiner. */
{
  fprintf(stderr, "dessiner : un simple composant ne peut pas être dessiné.\n");

  /* XSetForeground(recuperer_affichage(destination),
                 recuperer_contexte_graphique(destination), a_dessiner->couleur);
  XDrawPoint(recuperer_affichage(destination), recuperer_ecran(destination),
             recuperer_contexte_graphique(destination),
             (int) a_dessiner->x, (int) a_dessiner->y);
  XFlush(recuperer_affichage(destination)); */
}



/*
 * Détruit un composant.
 */
void detruire_composant(Composant a_detruire) /* Le composant à détruire. */
{
  /* La mémoire dédiée au composant est libérée. */
  free(a_detruire);
}
