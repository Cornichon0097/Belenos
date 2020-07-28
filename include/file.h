#ifndef PILE_H
#define PILE_H


typedef struct file * File;



File creer_file();

void enqueue(File f, void * composant);

void * dequeue(File f);

int empty(File f);

void clear(File f);

void detruire_file(File a_detruire);


#endif
