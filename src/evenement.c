#include <X11/Xlib.h>

#include "../include/evenement.h"



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
