#include <X11/Xlib.h>

#include "../include/evenement.h"



/*
 * Affiche une fenêtre à l'écran.
 */
void afficher_fenetre(Fenetre a_afficher) /* La fenêtre à afficher. */
{
  XEvent evenement; /* L'événement lié à la fenêtre. */


  /* Une fois les paramètres définis, la fenêtre peut être affichée à l'écran. */
  XMapWindow(recuperer_affichage(a_afficher), recuperer_ecran(a_afficher));

  do
  {
    /* En attente d'un événement d'exposition de la fenêtre. */
    XNextEvent(recuperer_affichage(a_afficher), &evenement);
  }
  while (evenement.type != Expose);
}



/*
 * Retourne si une fenêtre est ouverte.
 */
int est_ouverte(const Fenetre f) /* La fenêtre concernée. */
{
  XEvent evenement; /* L'événement lié à la fenêtre. */


  /* Si un événement du même type que celui de la fermeture de la fenêtre est en attente,
     alors il est récupéré afin de pouvoir en connaître la nature. */
  if (XCheckTypedEvent(recuperer_affichage(f), ClientMessage, &evenement))
  {
    /* Vérifie si l'événement correspond à la fermeture de la fenêtre. */
    if ((Atom) evenement.xclient.data.l[0] == fermeture(f))
    {
      return 0;
    }
  }

  /* Si un événement qui résulte d'une modification de la fenêtre est en attente,
     alors il est récupéré et la fenêtre est rafraîchie. */
  if (XCheckMaskEvent(recuperer_affichage(f), StructureNotifyMask, &evenement))
  {
    rafraichir(f);
  }


  /* Si les deux conditions précédentes ne sont pas remplies,
     alors la fenêtre est toujours ouverte. */
  return 1;
}



KeySym touche_pressee(const Fenetre f)
{
  XEvent evenement;


  if (XCheckMaskEvent(recuperer_affichage(f), KeyPressMask, &evenement))
  {
    return XLookupKeysym(&(evenement.xkey), 0);
  }
  else
  {
    return XK_VoidSymbol;
  }
}



KeySym touche_relachee(const Fenetre f)
{
  XEvent evenement;


  if (XCheckMaskEvent(recuperer_affichage(f), KeyReleaseMask, &evenement))
  {
    return XLookupKeysym(&(evenement.xkey), 0);
  }
  else
  {
    return XK_VoidSymbol;
  }
}
