#include "../include/composant.h"


struct composant
{
  signed char x;
  signed char y;
  couleur couleur;
};



Composant creer_composant(Fenetre f,
                          int x,
                          int y)
{
  XDrawPoint(recuperer_affichage(f), recuperer_ecran(f), recuperer_contexte_graphique(f),
             x, y);
  XFlush(recuperer_affichage(f));

  return NULL;
}
