#include <stdlib.h>
#include <stdio.h>

#include "../include/couleur.h"
#include "../include/fenetre.h"
#include "../include/point.h"
#include "../include/evenement.h"


#define X_FENETRE 100
#define Y_FENETRE 50
#define LARGEUR_FENETRE 500
#define HAUTEUR_FENETRE 500



int main(void)
{
  Fenetre f = creer_fenetre(X_FENETRE, Y_FENETRE, LARGEUR_FENETRE, HAUTEUR_FENETRE);
  int x, y;


  if (f == NULL)
  {
    fprintf(stderr, "Un problème s'est produit avec la fenêtre. Arrêt.\n");
    return EXIT_FAILURE;
  }

  afficher_fenetre(f);

  while (est_ouverte(f))
  {
    if (bouton_presse(f) == 1)
    {
      while (bouton_relache(f) != 1)
      {
        position_souris(f, &x, &y);
        ajouter(f, creer_point(x, y, NOIR));
      }
    }
  }

  detruire_fenetre(f);


  return EXIT_SUCCESS;
}
