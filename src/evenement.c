#include <X11/Xlib.h>

#include "../include/evenement.h"



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


  /* Retourne 1 si la fenêtre est toujours ouverte. */
  return 1;
}



/*
 * Retourne la touche du clavier pressée (si touche de clavier pressée il y a).
 */
KeySym touche_pressee(const Fenetre f) /* La fenêtre concernée. */
{
  XEvent evenement; /* L'événement lié à la fenêtre. */


  /* Vérifie qu'une touche du clavier a été pressée. */
  if (XCheckMaskEvent(recuperer_affichage(f), KeyPressMask, &evenement))
  {
    /* Si oui, elle est retournée. */
    return XLookupKeysym(&(evenement.xkey), 0);
  }
  else
  {
    /* Sinon, le symbole vide est retourné. */
    return XK_VoidSymbol;
  }
}



/*
 * Retourne la touche du clavier relâchée (si touche de clavier relâchée il y a).
 */
KeySym touche_relachee(const Fenetre f) /* La fenêtre concernée. */
{
  XEvent evenement; /* L'événement lié à la fenêtre. */


  /* Vérifie qu'une touche du clavier a été relâchée. */
  if (XCheckMaskEvent(recuperer_affichage(f), KeyReleaseMask, &evenement))
  {
    /* Si oui, elle est retournée. */
    return XLookupKeysym(&(evenement.xkey), 0);
  }
  else
  {
    /* Sinon, le symbole vide est retourné. */
    return XK_VoidSymbol;
  }
}



/*
 * Retourne le bouton de la souris pressé (si bouton de souris pressé il y a).
 */
unsigned int bouton_presse(const Fenetre f) /* La fenêtre concernée. */
{
  XEvent evenement; /* L'événement lié à la fenêtre. */


  /* Vérifie qu'un bouton de la souris a été pressé. */
  if (XCheckMaskEvent(recuperer_affichage(f), ButtonPressMask, &evenement))
  {
    /* Si oui, il est retourné. */
    return evenement.xbutton.button;
  }
  else
  {
    /* Sinon, le symbole vide est retourné. */
    return VIDE;
  }
}



/*
 * Retourne le bouton de la souris relâché (si bouton de souris relâché il y a).
 */
unsigned int bouton_relache(const Fenetre f) /* La fenêtre concernée. */
{
  XEvent evenement; /* L'événement lié à la fenêtre. */


  /* Vérifie qu'un bouton de la souris a été relâché. */
  if (XCheckMaskEvent(recuperer_affichage(f), ButtonReleaseMask, &evenement))
  {
    /* Si oui, il est retourné. */
    return evenement.xbutton.button;
  }
  else
  {
    /* Sinon, le symbole vide est retourné. */
    return VIDE;
  }
}
