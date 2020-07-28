#include <stdlib.h>

#include "../include/file.h"


struct maillon
{
  void * composant;
  struct maillon * suivant;
};


struct file
{
  struct maillon * premier;
  struct maillon * dernier;
};



File creer_file()
{
  File nouvelle = (File) malloc(sizeof(struct file));


  nouvelle->premier = NULL;
  nouvelle->dernier = NULL;


  return nouvelle;
}



void enqueue(File f, void * composant)
{
  struct maillon * nouveau = (struct maillon*) malloc(sizeof(struct maillon));


  if (nouveau)
  {
    nouveau->composant = composant;
    nouveau->suivant = NULL;

    if (f->premier == NULL)
    {
      f->premier = nouveau;
    }
    else
    {
      f->dernier->suivant = nouveau;
    }

    f->dernier = nouveau;
  }
}



void * dequeue(File f)
{
  struct maillon m = *(f->premier);


  free(f->premier);
  f->premier = m.suivant;

  if (f->premier == NULL)
  {
    f->dernier = NULL;
  }


  return m.composant;
}



int empty(File f)
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



void clear(File f)
{
  while (!empty(f))
  {
    dequeue(f);
  }
}



void detruire_file(File a_detruire)
{
  clear(a_detruire);
  free(a_detruire);
}
