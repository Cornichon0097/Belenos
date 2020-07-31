#ifndef COULEUR_H
#define COULEUR_H


typedef struct couleur* Couleur;


struct couleur_rvb
{
  unsigned char rouge;
  unsigned char vert;
  unsigned char bleu;
};



Couleur creer_couleur_hex(int hex);

Couleur creer_couleur_rvb(int rouge, int vert, int bleu);

unsigned long int recuperer_couleur_hex(Couleur c);

struct couleur_rvb recuperer_couleur_rvb(Couleur c);

void detruire_couleur(Couleur a_detruire);


#endif
