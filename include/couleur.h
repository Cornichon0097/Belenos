#ifndef COULEUR_H
#define COULEUR_H


/*
 * La structure d'une couleur.
 */
typedef struct couleur* Couleur;


/*
 * La structure de la représentation RVB d'une couleur.
 * La représentation RVB d'une couleur comporte trois composantes.
 */
struct couleur_rvb
{
  unsigned char rouge; /* La composante rouge. */
  unsigned char vert;  /* La composante verte. */
  unsigned char bleu;  /* La composante bleue. */
};



/*
 * Crée une couleur à partir de la représentation hexadécimale.
 */
Couleur creer_couleur_hex(int hex);

/*
* Crée une couleur à partir de la représentation RVB.
 */
Couleur creer_couleur_rvb(int rouge, int vert, int bleu);

/*
 * Retourne la représentation hexadécimale d'une couleur.
 */
unsigned long int recuperer_couleur_hex(Couleur c);

/*
* Retourne la représentation RVB d'une couleur.
 */
struct couleur_rvb recuperer_couleur_rvb(Couleur c);

/*
 * Détruit une couleur.
 */
void detruire_couleur(Couleur a_detruire);


#endif
