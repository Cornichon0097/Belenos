#include <stdlib.h>
#include <stdio.h>

#include "../include/couleur.h"
#include "../include/fenetre.h"
#include "../include/etiquette.h"


#define X_FENETRE 100
#define Y_FENETRE 50
#define LARGEUR_FENETRE 500
#define HAUTEUR_FENETRE 500



int main(void)
{
  Fenetre f = creer_fenetre(X_FENETRE, Y_FENETRE, LARGEUR_FENETRE, HAUTEUR_FENETRE);


  if (f == NULL)
  {
    fprintf(stderr, "Un problème s'est produit avec la fenêtre. Arrêt.\n");
    return EXIT_FAILURE;
  }

  afficher_fenetre(f);

  ajouter(f, creer_etiquette(10, 10, "Ceci est une étiquette.", creer_couleur_rvb(0xff, 0, 0xff)));

  while (est_ouverte(f))
  {
    /* printf("test\n"); */
  }

  detruire_fenetre(f);


  return EXIT_SUCCESS;
}
