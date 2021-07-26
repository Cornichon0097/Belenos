#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include <belenos/window.h>
#include <belenos/event.h>



int is_open(struct window * const window)
{
  XEvent event;

  /* if (XCheckTypedEvent(get_display(window), ClientMessage, &event))
   {
     if ((Atom) event.xclient.data.l[0] == get_close_operation(window))
     {
       return 0;
     }
   } */

  /* Waiting for new event. */
  XNextEvent(get_display(window), &event);

  if ((event.type == ClientMessage)
      && (((Atom) event.xclient.data.l[0]) == get_close_operation(window)))
  {
    return 0;
  }

  return 1;
}
