#include <stdlib.h>
#include <stdio.h>

#include "../include/couleur.h"
#include "../include/fenetre.h"
#include "../include/evenement.h"


#define X_FENETRE 100
#define Y_FENETRE 50
#define LARGEUR_FENETRE 700U
#define HAUTEUR_FENETRE 500U



int main(void)
{
  Fenetre f = creer_fenetre(X_FENETRE, Y_FENETRE, LARGEUR_FENETRE, HAUTEUR_FENETRE);
  Composant c = creer_composant();


  if (f == NULL)
  {
    fprintf(stderr, "Un problème s'est produit avec la fenêtre. Arrêt.\n");
    return EXIT_FAILURE;
  }

  afficher_fenetre(f);
  changer_arriere_plan(c, ROUGE);

  ajouter(f, c);

  while (est_ouverte(f)) {}

  detruire_fenetre(f);


  return EXIT_SUCCESS;
}
