#include <stdlib.h>
#include <stdio.h>

#include "../include/fenetre.h"
#include "../include/file.h"

#define NOMBRE_ECRANS 5  /* Le nombre d'écrans disponibles pour dessiner. */
#define BORDURE       1U /* La taille des bordures de la fenêtre. */


/*
 * La structure d'une fenêtre.
 * Il s'agit de la structure principale de l'application. La fenêtre permet l'affichage
 * de composants graphiques de différentes natures. De plus, elle centralise la majorité
 * des allocations dynamiques afin de libérer toute la mémoire avec une seule fonction.
 * Enfin, la fenêtre comprend plusieurs écrans pour dessiner. Un composant graphique
 * ajouté à la fenêtre peut être dessiné dans n'importe quel écran, indépendemment des
 * autres. Cependant, seul le premier écran est affiché dans la fenêtre.
 */
struct fenetre
{
  Display * affichage;            /* L'affichage, structure principale de Xlib. */
  int ecran_par_defaut;           /* L'écran par défaut. */
  Window ecrans[NOMBRE_ECRANS];   /* Les écrans pour dessiner. */
  unsigned char ecran_actif;      /* L'écran actif. */
  XSetWindowAttributes attributs; /* Les attributs. */
  GC contexte_graphique;          /* Le contexte graphique. */
  Atom fermeture;                 /* L'action de fermeture. */
  File composants;                /* La file des composants graphiques. */
};



/*
 * Crée une nouvelle fenêtre.
 */
Fenetre creer_fenetre(int x,       /* L'abscisse, en pixels. */
                      int y,       /* L'ordonnée, en pixels. */
                      int largeur, /* La largeur, en pixels. */
                      int hauteur) /* La hauteur, en pixels. */
{
  Fenetre nouvelle; /* La nouvelle fenêtre. */
  int i;            /* Variable itérative. */


  /* Allocation d'un espace mémoire pour le composant. */
  nouvelle = (Fenetre) malloc(sizeof(struct fenetre));

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
    detruire_fenetre(nouvelle);
    return NULL;
  }

  /* L'écran par défaut. */
  nouvelle->ecran_par_defaut = XDefaultScreen(nouvelle->affichage);

  /* Création de la fenêtre. */
  nouvelle->ecrans[0] = XCreateSimpleWindow(nouvelle->affichage,
                                            XRootWindow(nouvelle->affichage,
                                                        nouvelle->ecran_par_defaut),
                                            x, y, (unsigned int) largeur,
                                            (unsigned int) hauteur, BORDURE,
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
  for (i = 1; i < NOMBRE_ECRANS; i++)
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

  /* Les événements gérés par la fenêtre. Ici, la fenêtre référencera dans une file
     dédiée les événements liés à l'exposition de la fenêtre, à la pression d'une
     touche du clavier et aux cliques de la souris. */
  XSelectInput(nouvelle->affichage, nouvelle->ecrans[0],
               ExposureMask            /* Exposition de la fenêtre. */
               | KeyPressMask          /* Touche de clavier pressée. */
               | KeyReleaseMask        /* Touche de clavier relâchée. */
               | ButtonPressMask       /* Bouton de souris pressé. */
               | ButtonReleaseMask     /* Bouton de souris relâché. */
               | StructureNotifyMask); /* Changement de structure de la fenêtre. */

  /* L'écran actif par défaut. */
  nouvelle->ecran_actif = 0U;

  /* Modification des attributs de la fenêtre pour un affichage permanent. */
  nouvelle->attributs.backing_store = Always;
  XChangeWindowAttributes(nouvelle->affichage, nouvelle->ecrans[nouvelle->ecran_actif],
                          CWBackingStore, &(nouvelle->attributs));

  /* Le contexte graphique de la fenêtre, indispensable pour dessiner. */
  nouvelle->contexte_graphique = XDefaultGC(nouvelle->affichage,
                                            nouvelle->ecran_par_defaut);

  /* L'action de fermeture par défaut de la fenêtre est de cliquer sur la croix. */
  nouvelle->fermeture = XInternAtom(nouvelle->affichage, "WM_DELETE_WINDOW", 0);
  XSetWMProtocols(nouvelle->affichage, nouvelle->ecrans[nouvelle->ecran_actif],
                  &(nouvelle->fermeture), 1);

  /* La file des composants graphiques. Tous les composants graphiques ajoutés à la
     à la fenêtre y seront répertoriés, afin de pouvoir libérer la mémoire qui leur
     est dédiée au moment de détruire la fenêtre. */
  nouvelle->composants = creer_file();

  /* XSetWindowBackground(nouvelle->affichage, nouvelle->ecrans[nouvelle->ecran_actif], 0x0); */
  XAutoRepeatOff(nouvelle->affichage);


  /* Retourne la nouvelle fenêtre. */
  return nouvelle;
}



/*
 * Retourne l'affichage d'une fenêtre.
 */
Display * recuperer_affichage(const Fenetre f) /* La fenêtre concernée. */
{
  /* Retourne l'affichage de la fenêtre. */
  return f->affichage;
}



/*
 * Modifie l'écran actif d'une fenêtre.
 */
void changer_ecran(Fenetre f,       /* La fenêtre concernée. */
                   int ecran_actif) /* Le nouvel écran actif. */
{
  fprintf(stdout, "Pas encore...\n");
  return;

  /* Vérifie que le nouvel écran actif existe. */
  if ((ecran_actif >= 0) && (ecran_actif < NOMBRE_ECRANS))
  {
    f->ecran_actif = (unsigned char) ecran_actif;
  }
  else
  {
    fprintf(stderr, "changer_ecran : l'écran %d n'existe pas.\n", ecran_actif);
  }
}



/*
 * Retourne l'écran actif d'une fenêtre.
 */
Window recuperer_ecran(const Fenetre f) /* La fenêtre concernée. */
{
  /* Retourne l'écran actif de la fenêtre. */
  return f->ecrans[0];
}



/*
 * Retourne le contexte graphique d'une fenêtre.
 */
GC recuperer_contexte_graphique(const Fenetre f) /* La fenêtre concernée. */
{
  /* Retourne le contexte graphique de la fenêtre. */
  return f->contexte_graphique;
}



Atom fermeture(const Fenetre f)
{
  return f->fermeture;
}



/*
 * Rafraîchit une fenêtre.
 */
void rafraichir(const Fenetre a_rafraichir) /* La fenêtre à rafraîchir. */
{
  struct maillon * m = top(a_rafraichir->composants); /* Le premier maillon. */


  /* Efface la fenêtre. */
  XClearWindow(a_rafraichir->affichage,
               a_rafraichir->ecrans[a_rafraichir->ecran_actif]);

  /* Tous les composants de la fenêtre sont redessinés. */
  while (m)
  {
    action(m->graphique).dessiner(m->graphique);
    /* Une fois le composant dessiné, on passe au suivant. */
    m = m->suivant;
  }
}



/*
 * Ajoute un composant à une fenêtre. Cette action a pour effet de dessiner le composant
 * ajouté dans la fenêtre destination, sur l'écran actif uniquement.
 */
void ajouter(const Fenetre destination, /* La fenêtre destination. */
             Composant a_ajouter)       /* Le composant à ajouter. */
{
  /* Vérifie que le composant à ajouter n'est pas nul. */
  if (a_ajouter == NULL)
  {
    fprintf(stderr, "ajouter : le composant à ajouté est nul.\n");
    return;
  }

  /* Le composant a besoin de connaître la fenêtre à laquelle il appartient. */
  changer_fenetre(destination, a_ajouter);
  /* Le composant est ajouté à la file des composants graphiques. */
  enqueue(destination->composants, a_ajouter);
  /* Une fois ajouté à la file, le composant est dessiné. */
  action(a_ajouter).dessiner(a_ajouter);
}



void position_souris(const Fenetre f, int * x, int * y)
{
  Window w, i;
  unsigned int mask;
  int root_x, root_y;


  XQueryPointer(f->affichage, f->ecrans[0], &w, &i, &root_x, &root_y, x, y, &mask);
}



/*
 * Détruit une fenêtre.
 */
void detruire_fenetre(Fenetre a_detruire) /* La fenêtre à détruire. */
{
  XAutoRepeatOn(a_detruire->affichage);
  /* Fermeture de l'affichage et de tout ce qui en dépend. */
  XCloseDisplay(a_detruire->affichage);
  /* La file des composants graphiques est détruite. */
  detruire_file(a_detruire->composants);
  /* La mémoire dédiée à la fenêtre est libérée. */
  free(a_detruire);
}
