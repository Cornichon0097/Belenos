#include <stdlib.h>
#include <stdio.h>
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
Etiquette creer_etiquette(int x,           /* L'abscisse, en pixels. */
                          int y,           /* L'ordonnée, en pixels. */
                          char * texte,    /* La chaîne de caractères. */
                          couleur couleur) /* La couleur. */
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
    fprintf(stderr, "creer_etiquette : impossible d'allouer une mémoire suffisante.\n");
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
void dessiner_etiquette(const Etiquette a_dessiner) /* L'étiquette à dessiner. */
{
  /* Les propriétés du composant qui en font une étiquette : */
  struct etiquette * etiquette = (struct etiquette*) recuperer_nature(a_dessiner);


  /* L'étiquette est dessinée. */
  XSetForeground(recuperer_affichage(recuperer_fenetre(a_dessiner)),
                 recuperer_contexte_graphique(recuperer_fenetre(a_dessiner)),
                 recuperer_couleur(a_dessiner));
  XDrawString(recuperer_affichage(recuperer_fenetre(a_dessiner)),
              recuperer_ecran(recuperer_fenetre(a_dessiner)),
              recuperer_contexte_graphique(recuperer_fenetre(a_dessiner)),
              recuperer_x(a_dessiner), recuperer_y(a_dessiner),
              etiquette->texte, (int) etiquette->longueur);
  XFlush(recuperer_affichage(recuperer_fenetre(a_dessiner)));
}



/*
 * Modifie le texte d'une étiquette.
 */
void changer_texte(Etiquette e,  /* L'étiquette concernée. */
                   char * texte) /* Le nouveau texte. */
{
  /* Les propriétés du composant qui en font une étiquette : */
  struct etiquette * etiquette = (struct etiquette*) recuperer_nature(e);


  /* Modifie le texte de l'étiquette. */
  etiquette->texte = texte;
  etiquette->longueur = strlen(texte);

  /* Rafraîchit la fenêtre si nécessaire. */
  if (recuperer_fenetre(e))
  {
    rafraichir(recuperer_fenetre(e));
  }
}



/*
 * Retourne le texte d'une étiquette.
 */
char * recuperer_texte(const Etiquette e) /* L'étiquette concernée. */
{
  /* Les propriétés du composant qui en font une étiquette : */
  struct etiquette * etiquette = (struct etiquette*) recuperer_nature(e);


  /* Retourne le texte de l'étiquette. */
  return etiquette->texte;
}



/*
 * Détruit une étiquette.
 */
void detruire_etiquette(Etiquette a_detruire) /* L'étiquette à détruire. */
{
  /* La mémoire dédiée à l'étiquette est libérée. */
  free(recuperer_nature(a_detruire));
  detruire_composant(a_detruire);
}
