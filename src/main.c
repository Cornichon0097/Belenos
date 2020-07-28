#include <stdlib.h>

#include "../include/fenetre.h"
#include "../include/composant.h"


#define X_FENETRE 100
#define Y_FENETRE 50
#define LARGEUR_FENETRE 500U
#define HAUTEUR_FENETRE 500U



int main(void)
{
  Fenetre f = creer_fenetre(X_FENETRE, Y_FENETRE, LARGEUR_FENETRE, HAUTEUR_FENETRE);


  if (f)
  {
    afficher_fenetre(f);

    while (est_ouverte(f))
    {
      creer_composant(f, 10, 10);
      /* printf("test\n"); */
    }

    detruire_fenetre(f);
  }


  return EXIT_SUCCESS;
}
