#include <stdlib.h>



struct panneau
{
  Window    ecran;
  Composant composant;
  Panneau * disposition;
};



Panneau creer_panneau(const Fenetre f, int x, int y, unsigned int largeur, unsigned int hauteur)
{
  Panneau nouveau = (Panneau) malloc(sizeof(struct panneau));


  nouveau->ecran = XCreateSimpleWindow(recuperer_affichage(f), recuperer_ecran(f),
                                       x, y, largeur, hauteur, BORDURE, )


  return nouveau;
}
