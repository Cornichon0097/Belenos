#include <stdlib.h>
#include <stdio.h>

#include "../include/couleur.h"
#include "../include/fenetre.h"
#include "../include/rectangle.h"
#include "../include/evenement.h"


#define X_FENETRE 100
#define Y_FENETRE 50
#define LARGEUR_FENETRE 500
#define HAUTEUR_FENETRE 500



unsigned int difference_positive(int a, int b)
{
  if (a > b)
  {
    return (unsigned int) (a - b);
  }
  else
  {
    return (unsigned int) (b - a);
  }
}



int main(void)
{
  Fenetre f = creer_fenetre(X_FENETRE, Y_FENETRE, LARGEUR_FENETRE, HAUTEUR_FENETRE);
  int x, y, l, h;


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
      position_souris(f, &x, &y);
      printf("Clique !\n");
    }

    if (bouton_relache(f) == 1)
    {
      position_souris(f, &l, &h);
      ajouter(f, creer_rectangle(x, y, difference_positive(x, l), difference_positive(y, h), NOIR, 0));
      printf("Relaché !\n");
    }
  }

  detruire_fenetre(f);


  return EXIT_SUCCESS;
}
