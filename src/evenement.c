#include <X11/Xlib.h>

#include "../include/evenement.h"



KeySym touche(const Fenetre f)
{
  XEvent evenement;


  if (XCheckMaskEvent(recuperer_affichage(f), KeyPressMask, &evenement))
  {
    return XLookupKeysym(&(evenement.xkey), 0);
  }
  else
  {
    return 0;
  }
}
