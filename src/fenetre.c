#include <stdlib.h>
#include <stdio.h>

#include <X11/Xutil.h>

#include "../include/fenetre.h"
#include "../include/file.h"

#define BORDURE 1U /* La taille des bordures de la fenêtre. */


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
  Display * affichage;          /* L'affichage, structure principale de Xlib. */
  Window    ecran_principal;    /* L'écran pour dessiner. */
  GC        contexte_graphique; /* Le contexte graphique. */
  Atom      fermeture;          /* L'action de fermeture. */
  File      composants;         /* La file des composants graphiques. */
  /* Grille    gestionnaire; */
};



/*
 * Crée une nouvelle fenêtre.
 */
Fenetre creer_fenetre(int          x,       /* L'abscisse, en pixels. */
                      int          y,       /* L'ordonnée, en pixels. */
                      unsigned int largeur, /* La largeur, en pixels. */
                      unsigned int hauteur) /* La hauteur, en pixels. */
{
  Fenetre      nouvelle;         /* La nouvelle fenêtre. */
  XSizeHints * proprietes;       /* Les proprietés de la fenêtre. */
  int          ecran_par_defaut; /* L'écran par défaut. */


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

  ecran_par_defaut = XDefaultScreen(nouvelle->affichage);

  /* Création de la fenêtre. */
  nouvelle->ecran_principal = XCreateSimpleWindow(nouvelle->affichage,
                                                  XRootWindow(nouvelle->affichage,
                                                              ecran_par_defaut),
                                                  x, y, largeur, hauteur, BORDURE,
                                                  XBlackPixel(nouvelle->affichage,
                                                              ecran_par_defaut),
                                                  XWhitePixel(nouvelle->affichage,
                                                              ecran_par_defaut));

  /* Vérifie que la fenêtre a bien été créée. */
  if (nouvelle->ecran_principal == 0)
  {
    fprintf(stderr, "creer_fenetre : impossible de créer la fenêtre.\n");
    detruire_fenetre(nouvelle);
    return NULL;
  }

  /* La position demadée pour la nouvelle fenêtre peut ne pas être prise en compte lors
     de sa création. Il faut donc essayé de régler le problème. */
  proprietes = XAllocSizeHints();

  if (proprietes)
  {
    proprietes->flags = PPosition;
    proprietes->x     = x;
    proprietes->y     = y;

    /* Application des proprietés souhaitées à la fenêtre. */
    XSetWMNormalHints(nouvelle->affichage, nouvelle->ecran_principal, proprietes);
    XFree(proprietes);
  }
  else
  {
    fprintf(stderr, "creer_fenetre : impossible de placer ");
    fprintf(stderr, "la fenêtre aux coordonnées demadées.\n");
  }

  /* Les événements gérés par la fenêtre. Ici, la fenêtre référencera dans une file
     dédiée les événements liés à l'exposition de la fenêtre, à la pression d'une
     touche du clavier et aux cliques de la souris. */
  XSelectInput(nouvelle->affichage, nouvelle->ecran_principal,
               ExposureMask            /* Exposition de la fenêtre. */
               | KeyPressMask          /* Touche de clavier pressée. */
               | KeyReleaseMask        /* Touche de clavier relâchée. */
               | ButtonPressMask       /* Bouton de souris pressé. */
               | ButtonReleaseMask     /* Bouton de souris relâché. */
               | StructureNotifyMask); /* Changement de structure de la fenêtre. */

  /* Le contexte graphique de la fenêtre, indispensable pour dessiner. */
  nouvelle->contexte_graphique = XDefaultGC(nouvelle->affichage, ecran_par_defaut);

  /* La file des composants graphiques. Tous les composants graphiques ajoutés à la
     à la fenêtre y seront répertoriés, afin de pouvoir libérer la mémoire qui leur
     est dédiée au moment de détruire la fenêtre. */
  nouvelle->composants = creer_file();

  if (nouvelle->composants == NULL)
  {
    fprintf(stderr, "creer_fenetre : impossible de créer la file des composants.\n");
    detruire_fenetre(nouvelle);
    return NULL;
  }

  /* XSetWindowBackground(nouvelle->affichage, nouvelle->ecran, 0x0); */
  /* XAutoRepeatOff(nouvelle->affichage); */


  /* Retourne la nouvelle fenêtre. */
  return nouvelle;
}



/*
 * Affiche une fenêtre à l'écran.
 */
void afficher_fenetre(Fenetre a_afficher) /* La fenêtre à afficher. */
{
  XSetWindowAttributes attributs; /* Les attributs de la fenêtre. */
  XEvent               evenement; /* L'événement lié à la fenêtre. */


  /* Modification des attributs de la fenêtre pour un affichage permanent. */
  attributs.backing_store = Always;
  XChangeWindowAttributes(a_afficher->affichage, a_afficher->ecran_principal,
                          CWBackingStore, &attributs);

  /* L'action de fermeture par défaut de la fenêtre est de cliquer sur la croix. */
  a_afficher->fermeture = XInternAtom(a_afficher->affichage, "WM_DELETE_WINDOW", 0);
  XSetWMProtocols(a_afficher->affichage, a_afficher->ecran_principal,
                  &(a_afficher->fermeture), 1);

  /* Une fois les paramètres définis, la fenêtre peut être affichée à l'écran. */
  XMapWindow(a_afficher->affichage, a_afficher->ecran_principal);

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
Display * recuperer_affichage(const Fenetre f) /* La fenêtre concernée. */
{
  /* Retourne l'affichage de la fenêtre. */
  return f->affichage;
}



/*
 * Retourne l'écran actif d'une fenêtre.
 */
Window recuperer_ecran_principal(const Fenetre f) /* La fenêtre concernée. */
{
  /* Retourne l'écran actif de la fenêtre. */
  return f->ecran_principal;
}



/*
 * Retourne le contexte graphique d'une fenêtre.
 */
GC recuperer_contexte_graphique(const Fenetre f) /* La fenêtre concernée. */
{
  /* Retourne le contexte graphique de la fenêtre. */
  return f->contexte_graphique;
}



/*
 * Retourne le mode de fermeture d'une fenêtre.
 */
Atom fermeture(const Fenetre f) /* La fenêtre concernée. */
{
  /* Retourne le mode de fermeture de la fenêtre. */
  return f->fermeture;
}



/*
 * Rafraîchit une fenêtre.
 */
void rafraichir(const Fenetre a_rafraichir) /* La fenêtre à rafraîchir. */
{
  struct maillon *  m = top(a_rafraichir->composants); /* Le premier maillon. */


  /* Efface la fenêtre. */
  XClearWindow(a_rafraichir->affichage, a_rafraichir->ecran_principal);

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
             Composant     a_ajouter)   /* Le composant à ajouter. */
{
  /* Vérifie que le composant à ajouter n'est pas nul. */
  if (a_ajouter == NULL)
  {
    fprintf(stderr, "ajouter() : le composant à ajouté est nul.\n");
    return;
  }

  changer_fenetre(a_ajouter, destination);
  changer_ecran(a_ajouter, destination->ecran_principal);
  /* Le composant est ajouté à la file des composants graphiques. */
  enqueue(destination->composants, a_ajouter);
  /* Une fois ajouté à la file, le composant est dessiné. */
  action(a_ajouter).dessiner(a_ajouter);
}



/*
 * Détruit une fenêtre.
 */
void detruire_fenetre(Fenetre a_detruire) /* La fenêtre à détruire. */
{
  /* XAutoRepeatOn(a_detruire->affichage); */
  /* Fermeture de l'affichage et de tout ce qui en dépend. */
  XCloseDisplay(a_detruire->affichage);
  /* La file des composants graphiques est détruite. */
  detruire_file(a_detruire->composants);
  /* La mémoire dédiée à la fenêtre est libérée. */
  free(a_detruire);
}
