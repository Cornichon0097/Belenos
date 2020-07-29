#include <stdlib.h>

#include "../include/file.h"


/*
 * La structure d'un maillon.
 * Un maillon se caractérise par l'information (composant) qu'il contient. Il permet
 * aussi d'accéder au maillon suivant da la liste chaînée.
 */
struct maillon
{
  Composant graphique;      /* Le composant. */
  struct maillon * suivant; /* Le maillon suivant. */
};


/*
 * La structure d'une file.
 * La file est une liste chaînée composée de maillons. Seules les adresses du premier et
 * du dernier maillon de la file sont sauvegardées. Les autres maillons sont accessibles
 * à partir de ceux qui les précèdent.
 */
struct file
{
  struct maillon * premier; /* Le premier maillon. */
  struct maillon * dernier; /* Le dernier maillon. */
};



/*
 * Crée une nouvelle file.
 */
File creer_file()
{
  File nouvelle = (File) malloc(sizeof(struct file)); /* La nouvelle file. */


  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouvelle)
  {
    /* Initialisation de la file. */
    nouvelle->premier = NULL;
    nouvelle->dernier = NULL;
  }


  /* Retourne la nouvelle file. */
  return nouvelle;
}



/*
 * Ajoute un composant à (la fin d') une file.
 */
void enqueue(File destination,    /* La file destination. */
             Composant a_ajouter) /* Le composant à ajouter. */
{
  struct maillon * nouveau = (struct maillon*) malloc(sizeof(struct maillon)); /* Le nouveau maillon. */


  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouveau)
  {
    nouveau->graphique = a_ajouter;
    /* Le nouveau maillon est ajouté à la fin de la file, il n'a donc pas de suivant. */
    nouveau->suivant = NULL;

    /* Si aucun autre maillon n'est présent dans la file, alors le dernier maillon est
       aussi le premier. */
    if (destination->premier == NULL)
    {
      destination->premier = nouveau;
    }
    /* Sinon, le nouveau maillon devient le suivant du dernier. */
    else
    {
      destination->dernier->suivant = nouveau;
    }

    /* Le nouveau maillon est maintenant le dernier de la file. */
    destination->dernier = nouveau;
  }
}



/*
 * Retourne le composant le plus ancien d'une file. Le maillon qui le contient est
 * retiré de la file.
 */
Composant dequeue(File f) /* La file concernée. */
{
  /* Le dernier maillon étant le plus récent, le plus ancien est le premier. */
  struct maillon m = *(f->premier); /* Copie temporaire du maillon qui sera retiré. */


  /* La mémoire dédiée au maillon est libérée. */
  free(f->premier);
  /* Le premier maillon de la file est maintenant celui qui était second. */
  f->premier = m.suivant;

  /* Si le maillon retiré n'avait pas de suivant, alors c'était le dernier de la file.
     Par conséquent, la file est maintenant vide. */
  if (f->premier == NULL)
  {
    f->dernier = NULL;
  }


  /* Retourne le composant le plus ancien de la file. */
  return m.graphique;
}



/*
 * Retourne si une file est vide.
 */
int empty(File f) /* La file concernée. */
{
  if (f->premier == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}



/*
 * Retire tous les maillons d'une file.
 */
void clear(File f) /* La file concernée. */
{
  Composant a_detruire; /* Le composant à détruire. */


  /* Tant que la file n'est pas vide, le maillon le plus ancien est retiré. */
  while (!empty(f))
  {
    a_detruire = dequeue(f);
    action(a_detruire).detruire(a_detruire);
  }
}



/*
 * Détruit une file.
 */
void detruire_file(File a_detruire) /* La file à détruire. */
{
  /* La file est vidée de tous ses maillons. */
  clear(a_detruire);
  /* La mémoire dédiée à la file est libérée. */
  free(a_detruire);
}
