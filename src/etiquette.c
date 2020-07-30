#include <stdlib.h>
#include <string.h>

#include "../include/etiquette.h"


/*
 * La structure d'une étiquette.
 * L'étiquette est un composant doté d'une chaîne de caractères.
 */
struct etiquette
{
  char * texte;          /* La chaîne de caractères. */
  unsigned int longueur; /* La longueur de la chaîne de caractères. */
};



/*
 * Crée une nouvelle étiquette.
 */
Etiquette creer_etiquette(int x, int y, char * texte, couleur couleur)
{
  /* La nouvelle étiquette : */
  Etiquette nouvelle = creer_composant(x, y, couleur);
  struct etiquette * etiquette = (struct etiquette*) malloc(sizeof(struct etiquette));


  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (etiquette)
  {
    /* Initialisation de l'étiquette. */
    etiquette->texte = texte;
    etiquette->longueur = strlen(texte);
  }
  /* Sinon, la création de l'étiquette est abandonnée. */
  else
  {
    detruire_composant(nouvelle);
    nouvelle = NULL;
  }

  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouvelle)
  {
    /* Initialisation de l'étiquette. */
    changer_action_dessiner(nouvelle, &dessiner_etiquette);
    changer_action_detruire(nouvelle, &detruire_etiquette);
    changer_nature(nouvelle, etiquette);
  }


  /* Retourne la nouvelle étiquette. */
  return nouvelle;
}



/*
 * Dessine une étiquette.
 */
void dessiner_etiquette(const Fenetre destination, const Etiquette a_dessiner)
{
  /* Les propriétés du composant qui en font une étiquette : */
  struct etiquette * etiquette = (struct etiquette*) recuperer_nature(a_dessiner);


  /* Dessine l'étiquette. */
  XSetForeground(recuperer_affichage(destination),
                 recuperer_contexte_graphique(destination),
                 recuperer_couleur(a_dessiner));
  XDrawString(recuperer_affichage(destination), recuperer_ecran(destination),
              recuperer_contexte_graphique(destination),
              recuperer_x(a_dessiner), recuperer_y(a_dessiner),
              etiquette->texte, (int) etiquette->longueur);
  XFlush(recuperer_affichage(destination));
}



/*
 * Détruit une étiquette.
 */
void detruire_etiquette(Etiquette a_detruire)
{
  /* La mémoire dédiée à l'étiquette est libérée. */
  free((struct etiquette*) recuperer_nature(a_detruire));
  detruire_composant(a_detruire);
}
