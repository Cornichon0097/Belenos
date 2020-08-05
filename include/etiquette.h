#ifndef ETIQUETTE_H
#define ETIQUETTE_H

#include "../include/composant.h"


/*
 * La structure d'une étiquette.
 */
typedef struct composant* Etiquette;



/*
 * Crée une nouvelle étiquette.
 */
Etiquette creer_etiquette(int x, int y, char * texte, Couleur couleur);

/*
 * Dessine une étiquette.
 */
void dessiner_etiquette(const Etiquette a_dessiner);

/*
 * Détruit une étiquette.
 */
void detruire_etiquette(Etiquette a_detruire);


#endif
