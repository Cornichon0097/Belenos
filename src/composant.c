#include <stdlib.h>

#include "../include/composant.h"


struct composant
{
  signed char x;
  signed char y;
  couleur couleur;
};



Composant creer_composant(int x,
                          int y,
                          couleur c)
{
  Composant nouveau = (Composant) malloc(sizeof(struct composant));


  nouveau->x = x;
  nouveau->y = y;
  nouveau->couleur = c;


  return nouveau;
}



void dessiner_composant(const Fenetre destination,
                        const Composant a_dessiner)
{
  XSetForeground(recuperer_affichage(destination),
                 recuperer_contexte_graphique(destination), a_dessiner->couleur);
  XDrawPoint(recuperer_affichage(destination), recuperer_ecran(destination),
             recuperer_contexte_graphique(destination), a_dessiner->x, a_dessiner->y);
  XFlush(recuperer_affichage(destination));
}



void detruire_composant(Composant a_detruire)
{
  free(a_detruire);
}
