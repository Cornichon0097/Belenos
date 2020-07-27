#include <stdlib.h>
#include <stdio.h>

#include "../include/fenetre.h"

#define BORDURE 1U


/*
 * La structure d'une fenêtre.
 */
struct fenetre
{
  Display * affichage;            /* L'affichage. */
  int ecran_par_defaut;           /* L'écran par défaut. */
  Window fenetre;                 /* Le fenêtre à l'écran. */
  XSetWindowAttributes attributs; /* Les attributs de la fenêtre. */
  GC contexte_graphique;          /* Le contexte graphique. */
  Atom fermeture;                 /*  */
};



/*
 * Crée une nouvelle fenêtre.
 */
Fenetre creer_fenetre(int x,                /* L'abscisse de la fenêtre à l'écran, en pixels. */
                      int y,                /* L'ordonnée de la fenêtre à l'écran, en pixels. */
                      unsigned int largeur, /* La largeur de la fenêtre, en pixels. */
                      unsigned int hauteur) /* La hauteur de la fenêtre, en pixels. */
{
  Fenetre nouvelle = (Fenetre) malloc(sizeof(struct fenetre)); /* La nouvelle fenêtre. */


  /* Connexion au serveur X. */
  nouvelle->affichage = XOpenDisplay(NULL);

  /* Une connexion au serveur X est nécessaire pour toutes les autres fonctions. */
  if (nouvelle->affichage == NULL)
  {
    fprintf(stderr, "Impossible d'établir la connexion avec le serveur %s.\n",
            XDisplayName(NULL));
    detruire_fenetre(nouvelle);
    return NULL;
  }

  /* L'écran par défaut. */
  nouvelle->ecran_par_defaut = XDefaultScreen(nouvelle->affichage);

  /* Création de la fenêtre. */
  nouvelle->fenetre = XCreateSimpleWindow(nouvelle->affichage,
                                          RootWindow(nouvelle->affichage,
                                                     nouvelle->ecran_par_defaut),
                                          x, y, largeur, hauteur, BORDURE,
                                          BlackPixel(nouvelle->affichage,
                                                     nouvelle->ecran_par_defaut),
                                          WhitePixel(nouvelle->affichage,
                                                     nouvelle->ecran_par_defaut));

  /* Les événements gérés par la fenêtre. */
  XSelectInput(nouvelle->affichage, nouvelle->fenetre,
               ExposureMask | KeyPressMask | ButtonPressMask);

  /* Le contexte graphique de la fenêtre. */
  nouvelle->contexte_graphique = DefaultGC(nouvelle->affichage,
                                           nouvelle->ecran_par_defaut);


  /* Retourne la nouvelle fenêtre. */
  return nouvelle;
}



/*
 * Affiche une fenêtre à l'écran.
 */
void afficher_fenetre(Fenetre a_afficher) /* La fenêtre à afficher. */
{
  XEvent evenement; /* L'événement lié à la fenêtre. */


  /* Modification des attributs de la fenêtre pour un affichage permanent. */
  a_afficher->attributs.backing_store = Always;
  XChangeWindowAttributes(a_afficher->affichage, a_afficher->fenetre,
                          CWBackingStore, &(a_afficher->attributs));

  /* L'action de fermeture par défaut de la fenêtre est de cliquer sur la petite croix. */
  a_afficher->fermeture = XInternAtom(a_afficher->affichage, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(a_afficher->affichage, a_afficher->fenetre, &(a_afficher->fermeture), 1);

  /* Ajout le fenêtre à l'écran. */
  XMapWindow(a_afficher->affichage, a_afficher->fenetre);

  do
  {
    /* En attente d'un événement d'exposition de la fenêtre. */
    XNextEvent(a_afficher->affichage, &evenement);
  }
  while (evenement.type != Expose);
}



/*
 * Retourne l'affichage de la fenêtre.
 */
Display * recuperer_affichage(Fenetre f)
{
  return f->affichage;
}



/*
 * Retourne la fenêtre d'une fenêtre.
 */
Window recuperer_fenetre(Fenetre f)
{
  return f->fenetre;
}



/*
 * Retourne le contexte graphique d'une fenêtre.
 */
GC recuperer_contexte_graphique(Fenetre f)
{
  return f->contexte_graphique;
}



/*
 * Retourne si la fenêtre est ouverte.
 */
int est_ouverte(Fenetre f)
{
  XEvent evenement; /* L'événement lié à la fenêtre. */


  /* Si un événement est en attente, il est récupéré. */
  if (XCheckTypedEvent(f->affichage, ClientMessage, &evenement))
  {
    /* Si cet événement correspond à la fermeture de la fenêtre : */
    if (evenement.xclient.data.l[0] == f->fermeture)
    {
      return 0;
    }
  }


  /* Sinon, la fenêtre est toujours ouverte. */
  return 1;
}



/*
 * Détruit une fenêtre.
 */
void detruire_fenetre(Fenetre a_detruire) /* La fenêtre à detruire. */
{
  /* Fermeture de l'affichage. */
  XCloseDisplay(a_detruire->affichage);
  /* La mémoire dédiée à la fenêtre est libérée. */
  free(a_detruire);
}
