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



int plus_petit(int a, int b)
{
  if (a < b)
  {
    return a;
  }
  else
  {
    return b;
  }
}



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
  Rectangle tableau[10]; /* Problèmes avec l'allocation dynamique (raison inconnue). */
  unsigned int index = 0, nouveau_rectangle = 1, i;
  int a, b, x, y, l, h;


  if (f == NULL)
  {
    fprintf(stderr, "Un problème s'est produit avec la fenêtre. Arrêt.\n");
    return EXIT_FAILURE;
  }

  afficher_fenetre(f);

  while (est_ouverte(f))
  {
    if (bouton_presse(f) == CLIQUE_GAUCHE)
    {
      position_souris(f, &x, &y);

      for (i = 0; i < index; i++)
      {
        if ((recuperer_x(tableau[i]) < x) && (recuperer_y(tableau[i]) < y)
            && (recuperer_x(tableau[i]) + recuperer_largeur(tableau[i]) > x)
            && (recuperer_y(tableau[i]) + recuperer_hauteur(tableau[i]) > y))
        {
          changer_remplissage(tableau[i], !recuperer_remplissage(tableau[i]));
          nouveau_rectangle = 0;
        }
      }
    }

    if (bouton_relache(f) == CLIQUE_GAUCHE)
    {
      if (nouveau_rectangle)
      {
        position_souris(f, &l, &h);

        a = plus_petit(x, l);
        b = plus_petit(y, h);

        tableau[index] = creer_rectangle(a, b, difference_positive(x, l),
                                         difference_positive(y, h), NOIR, VIDE);

        ajouter(f, tableau[index++]);
      }

      nouveau_rectangle = 1;
    }
  }

  detruire_fenetre(f);


  return EXIT_SUCCESS;
}
