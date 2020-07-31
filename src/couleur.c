#include <stdlib.h>
#include <stdio.h>

#include "../include/couleur.h"


/*
 * La structure d'une couleur.
 * La couleur est représentée par ses formes hexadécimale et RVB.
 */
struct couleur
{
  unsigned int hex;       /* La représentation en hexadécimale. */
  struct couleur_rvb rvb; /* La représentation RVB. */
};



/*
 * Crée une nouvelle couleur.
 */
Couleur creer_couleur(int hex,   /* La représentation hexadécimale. */
                      int rouge, /* La composante RVB rouge. */
                      int vert,  /* La composante RVB verte. */
                      int bleu)  /* La composante RVB bleue. */
{
  Couleur nouvelle = (Couleur) malloc(sizeof(struct couleur)); /* La nouvelle couleur. */


  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouvelle)
  {
    /* Initialisation de la couleur. */
    nouvelle->hex = (unsigned int) hex;
    nouvelle->rvb.rouge = (unsigned char) rouge;
    nouvelle->rvb.vert = (unsigned char) vert;
    nouvelle->rvb.bleu = (unsigned char) bleu;
  }


  /* Retourne la nouvelle couleur. */
  return nouvelle;
}



/*
 * Crée une couleur à partir de la représentation hexadécimale.
 */
Couleur creer_couleur_hex(int hex) /* La représentation hexadécimale. */
{
  /* Retourne la nouvelle couleur. */
  return creer_couleur(hex, ((hex & 0xff0000) >> 16), /* Le rouge. */
                            ((hex & 0xff00) >> 8),    /* Le vert. */
                            (hex & 0xff));            /* Le bleu. */
}



/*
* Crée une couleur à partir de la représentation RVB.
 */
Couleur creer_couleur_rvb(int rouge, /* La composante RVB rouge. */
                          int vert,  /* La composante RVB verte. */
                          int bleu)  /* La composante RVB bleue. */
{
  /* Retourne la nouvelle couleur. */
  return creer_couleur((rouge * 65536 + vert * 256 + bleu), rouge, vert, bleu);
}



/*
 * Retourne la représentation hexadécimale d'une couleur.
 */
unsigned long int recuperer_couleur_hex(Couleur c) /* La couleur concernée. */
{
  /* Retourne la représentation hexadécimale de la couleur. */
  return (unsigned long int) c->hex;
}



/*
* Retourne la représentation RVB d'une couleur.
 */
struct couleur_rvb recuperer_couleur_rvb(Couleur c) /* La couleur concernée. */
{
  /* Retourne la représentation RVB de la couleur. */
  return c->rvb;
}



/*
 * Détruit une couleur.
 */
void detruire_couleur(Couleur a_detruire) /* La couleur à détruire. */
{
  /* La mémoire dédiée à la couleur est libérée. */
  free(a_detruire);
}
