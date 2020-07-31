#include <stdlib.h>
#include <stdio.h>

#include "../include/couleur.h"


struct couleur
{
  unsigned int hex;
  struct couleur_rvb rvb;
};



Couleur creer_couleur(int hex, int rouge, int vert, int bleu)
{
  Couleur nouvelle = (Couleur) malloc(sizeof(struct couleur));


  if (nouvelle)
  {
    nouvelle->hex = (unsigned int) hex;
    nouvelle->rvb.rouge = (unsigned char) rouge;
    nouvelle->rvb.vert = (unsigned char) vert;
    nouvelle->rvb.bleu = (unsigned char) bleu;
  }


  return nouvelle;
}



Couleur creer_couleur_hex(int hex)
{
  return creer_couleur(hex, ((hex & 0xff0000) >> 16), /* Le rouge. */
                            ((hex & 0xff00) >> 8),    /* Le vert. */
                            (hex & 0xff));            /* Le bleu. */
}



Couleur creer_couleur_rvb(int rouge, int vert, int bleu)
{
  return creer_couleur((rouge * 65536 + vert * 256 + bleu), rouge, vert, bleu);
}



unsigned long int recuperer_couleur_hex(Couleur c)
{
  return (unsigned long int) c->hex;
}



struct couleur_rvb recuperer_couleur_rvb(Couleur c)
{
  return c->rvb;
}



void detruire_couleur(Couleur a_detruire)
{
  free(a_detruire);
}
