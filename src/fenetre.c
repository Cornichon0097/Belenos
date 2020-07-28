#include <stdlib.h>
#include <stdio.h>

#include "../include/fenetre.h"
#include "../include/file.h"

#define NOMBRE_D_ECRANS 5U
#define BORDURE 1U


/*
 * La structure d'une fenêtre.
 */
struct fenetre
{
  Display * affichage;            /* L'affichage. */
  int ecran_par_defaut;           /* L'écran par défaut. */
  Window ecrans[NOMBRE_D_ECRANS]; /* Les écrans pour dessiner. */
  unsigned char ecran_actif;      /* L'écran actif. */
  XSetWindowAttributes attributs; /* Les attributs. */
  GC contexte_graphique;          /* Le contexte graphique. */
  Atom fermeture;                 /* L'action de fermeture. */
  File composants;                /* La file des composants graphiques. */
};



/*
 * Crée une nouvelle fenêtre.
 */
Fenetre creer_fenetre(int x,                /* L'abscisse de la fenêtre, en pixels. */
                      int y,                /* L'ordonnée de la fenêtre, en pixels. */
                      unsigned int largeur, /* La largeur de la fenêtre, en pixels. */
                      unsigned int hauteur) /* La hauteur de la fenêtre, en pixels. */
{
  Fenetre nouvelle = (Fenetre) malloc(sizeof(struct fenetre)); /* La nouvelle fenêtre. */
  unsigned char i;                                             /* Variable itérative. */


  /* Vérifie que l'allocation dynamique s'est bien passée. */
  if (nouvelle == NULL)
  {
    fprintf(stderr, "creer_fenetre : impossible d'allouer une mémoire suffisante.\n");
    return NULL;
  }

  /* Connexion au serveur X. */
  nouvelle->affichage = XOpenDisplay(NULL);

  /* Vérifie que la connexion au serveur X a réussi. */
  if (nouvelle->affichage == NULL)
  {
    fprintf(stderr, "creer_fenetre : impossible d'établir la ");
    fprintf(stderr, "connexion avec le serveur %s.\n", XDisplayName(NULL));
    return NULL;
  }

  /* L'écran par défaut. */
  nouvelle->ecran_par_defaut = XDefaultScreen(nouvelle->affichage);

  /* Création de la fenêtre. */
  nouvelle->ecrans[0] = XCreateSimpleWindow(nouvelle->affichage,
                                            XRootWindow(nouvelle->affichage,
                                                       nouvelle->ecran_par_defaut),
                                            x, y, largeur, hauteur, BORDURE,
                                            XBlackPixel(nouvelle->affichage,
                                                       nouvelle->ecran_par_defaut),
                                            XWhitePixel(nouvelle->affichage,
                                                       nouvelle->ecran_par_defaut));

  /* Vérifie que la fenêtre a bien été créée. */
  if (nouvelle->ecrans[0] == 0)
  {
    fprintf(stderr, "creer_fenetre : impossible de créer la fenêtre.\n");
    detruire_fenetre(nouvelle);
    return NULL;
  }

  /* Création d'écrans non affichables. Il est cependant possible de s'en servir pour
     dessiner, au même titre que la fenêtre. */
  for (i = 1; i < NOMBRE_D_ECRANS; i++)
  {
    nouvelle->ecrans[i] = XCreatePixmap(nouvelle->affichage,
                                        XDefaultRootWindow(nouvelle->affichage),
                                        largeur, hauteur,
                                        XDefaultDepth(nouvelle->affichage,
                                                      nouvelle->ecran_par_defaut));

    /* Vérifie que les écrans ont bien été créés. */
    if (nouvelle->ecrans[i] == 0)
    {
      fprintf(stderr, "creer_fenetre : impossible de créer les écrans pour dessiner.\n");
      detruire_fenetre(nouvelle);
      return NULL;
    }
  }

  /* Les événements gérés par la fenêtre. */
  XSelectInput(nouvelle->affichage, nouvelle->ecrans[0],
               ExposureMask | KeyPressMask | ButtonPressMask);

  /* Le contexte graphique de la fenêtre. */
  nouvelle->contexte_graphique = XDefaultGC(nouvelle->affichage,
                                            nouvelle->ecran_par_defaut);

  nouvelle->composants = creer_file();


  /* Retourne la nouvelle fenêtre. */
  return nouvelle;
}



/*
 * Affiche une fenêtre à l'écran.
 */
void afficher_fenetre(Fenetre a_afficher) /* La fenêtre à afficher. */
{
  XEvent evenement; /* L'événement lié à la fenêtre. */


  /* L'écran actif. */
  a_afficher->ecran_actif = 0;

  /* Modification des attributs de la fenêtre pour un affichage permanent. */
  a_afficher->attributs.backing_store = Always;
  XChangeWindowAttributes(a_afficher->affichage,
                          a_afficher->ecrans[a_afficher->ecran_actif],
                          CWBackingStore, &(a_afficher->attributs));

  /* L'action de fermeture par défaut de la fenêtre est de cliquer sur la croix. */
  a_afficher->fermeture = XInternAtom(a_afficher->affichage, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(a_afficher->affichage, a_afficher->ecrans[a_afficher->ecran_actif],
                  &(a_afficher->fermeture), 1);

  /* Ajout le fenêtre à l'écran. */
  XMapWindow(a_afficher->affichage, a_afficher->ecrans[a_afficher->ecran_actif]);

  do
  {
    /* En attente d'un événement d'exposition de la fenêtre. */
    XNextEvent(a_afficher->affichage, &evenement);
  }
  while (evenement.type != Expose);
}



/*
 * Retourne l'affichage d'une fenêtre.
 */
Display * recuperer_affichage(const Fenetre f)
{
  return f->affichage;
}



/*
 * Retourne l'écran actif d'une fenêtre.
 */
Window recuperer_ecran(const Fenetre f)
{
  return f->ecrans[f->ecran_actif];
}



/*
 * Retourne le contexte graphique d'une fenêtre.
 */
GC recuperer_contexte_graphique(const Fenetre f)
{
  return f->contexte_graphique;
}



/*
 * Retourne si une fenêtre est ouverte.
 */
int est_ouverte(const Fenetre f)
{
  XEvent evenement; /* L'événement lié à la fenêtre. */


  /* Vérifie que la fenêtre existe. */
  if (f == NULL)
  {
    fprintf(stderr, "Votre fenêtre n'existe pas ou plus.\n");
    return 0;
  }

  /* Vérifie que la fenêtre a été créée correctement. */
  if (f->affichage == NULL)
  {
    fprintf(stderr, "Votre fenêtre n'est pas utilisable.\n");
    return 0;
  }

  /* Si un événement est en attente, il est récupéré. */
  if (XCheckTypedEvent(f->affichage, ClientMessage, &evenement))
  {
    /* Si cet événement correspond à la fermeture de la fenêtre : */
    if ((Atom) evenement.xclient.data.l[0] == f->fermeture)
    {
      return 0;
    }
  }


  /* Sinon, la fenêtre est toujours ouverte. */
  return 1;
}



/*
 * Ajoute un composant à une fenêtre.
 */
void ajouter(const Fenetre f, void * a_ajouter)
{
  enqueue(f->composants, a_ajouter);
}



/*
 * Détruit une fenêtre.
 */
void detruire_fenetre(Fenetre a_detruire) /* La fenêtre à detruire. */
{
  /* Fermeture de l'affichage et de tout ce qui en est lié. */
  XCloseDisplay(a_detruire->affichage);

  detruire_file(a_detruire->composants);

  /* La mémoire dédiée à la fenêtre est libérée. */
  free(a_detruire);
}
