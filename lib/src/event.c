#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include <belenos/event.h>



int b_is_open(b_frame_s * const frame)
{
  XEvent event;

  /* if (XCheckTypedEvent(get_display(frame), ClientMessage, &event))
   {
     if ((Atom) event.xclient.data.l[0] == get_close_operation(frame))
     {
       return 0;
     }
   } */

  /* Waiting for new event. */
  XNextEvent(b_get_display(frame), &event);

  if ((event.type == ClientMessage)
      && (((Atom) event.xclient.data.l[0]) == b_get_close_operation(frame)))
  {
    return 0;
  }

  return 1;
}
