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



void enqueue(File * f, void * composant)
{
  struct maillon * nouveau = (struct maillon*) malloc(sizeof(struct maillon));


  nouveau->composant = composant;
  nouveau->suivant = NULL;
}



void * dequeue(File * f)
{

}



int empty(File f)
{
  if (f == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}



void detruire_file()
