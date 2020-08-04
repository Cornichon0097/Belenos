#ifndef FILE_H
#define FILE_H

#include "../include/composant.h"


/*
 * La structure d'une file.
 */
typedef struct file* File;


/*
 * La structure d'un maillon.
 * Un maillon se caractérise par l'information (composant et écran) qu'il contient.
 * Il permet aussi d'accéder au maillon suivant da la liste chaînée.
 */
struct maillon
{
  Composant graphique;      /* Le composant. */
  struct maillon * suivant; /* Le maillon suivant. */
};



/*
 * Crée une nouvelle file.
 */
File creer_file();

/*
 * Ajoute un composant à (la fin d') une file.
 */
void enqueue(File f, Composant c);

/*
 * Retourne le composant le plus ancien d'une file.
 * Le maillon qui le contient est retiré de la file.
 */
Composant dequeue(File f);

/*
 * Retourne si une file est vide.
 */
int empty(File f);

struct maillon * top(File f);

/*
 * Retire tous les maillons d'une file.
 */
void clear(File f);

/*
 * Détruit une file.
 */
void detruire_file(File a_detruire);


#endif
