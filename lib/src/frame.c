#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <belenos/frame.h>
#include <belenos/component.h>

#define BORDERWIDTH 1U


struct b_frame
{
  Display * display;
  int       default_screen;
  Window    window;
  GC        graphics_context;
  Atom      close_operation;
};



static int b_create_window(struct b_frame * const frame,
                           const int              x,
                           const int              y,
                           const unsigned int     width,
                           const unsigned int     height)
{
  frame->window = XCreateSimpleWindow(frame->display,
                                      XRootWindow(frame->display,
                                                  frame->default_screen),
                                      x, y, width, height, BORDERWIDTH,
                                      XBlackPixel(frame->display,
                                                  frame->default_screen),
                                      XWhitePixel(frame->display,
                                                  frame->default_screen));

  if (frame->window == 0UL)
  {
    return 0;
  }

  return 1;
}



static int b_set_hints(struct b_frame * const frame,
                       const int              x,
                       const int              y)
{
  XSizeHints * hints = XAllocSizeHints();

  if (hints == NULL)
  {
    return 0;
  }

  hints->flags = PPosition;
  hints->x     = x;
  hints->y     = y;

  XSetWMNormalHints(frame->display, frame->window, hints);
  XFree(hints);

  return 1;
}



static int b_set_graphic(struct b_frame * const frame,
                         const int              x,
                         const int              y,
                         const unsigned int     width,
                         const unsigned int     height)
{
  frame->default_screen   = XDefaultScreen(frame->display);
  frame->graphics_context = XDefaultGC(frame->display,
                                       frame->default_screen);

  return (b_create_window(frame, x, y, width, height)
          && b_set_hints(frame, x, y));
}



static void b_set_events(struct b_frame * const frame)
{
  XSetWindowAttributes attributes;

  XSelectInput(frame->display, frame->window, ExposureMask
                                            | KeyPressMask
                                            | KeyReleaseMask
                                            | ButtonPressMask
                                            | ButtonReleaseMask
                                            | StructureNotifyMask);

  attributes.backing_store = Always;
  XChangeWindowAttributes(frame->display, frame->window,
                          CWBackingStore, &attributes);

  frame->close_operation = XInternAtom(frame->display,
                                       "WM_DELETE_WINDOW", False);
  XSetWMProtocols(frame->display, frame->window,
                  &(frame->close_operation), 1);
}



struct b_frame * b_new_frame(const int          x,
                             const int          y,
                             const unsigned int width,
                             const unsigned int height)
{
  struct b_frame * frame;

  frame = (struct b_frame *) malloc(sizeof(struct b_frame));

  if (frame)
  {
    frame->display = XOpenDisplay(NULL);

    if (frame->display == NULL)
    {
      free(frame);
      return NULL;
    }

    if (!b_set_graphic(frame, x, y, width, height))
    {
      b_destroy_frame(frame);
      return NULL;
    }

    /* Multiple screens, for later. */
    /* for (size_t i = 1; i < NB_SCREENS; i++)
     {
       frame->screen[i] = XCreatePixmap(frame->display,
                                         XDefaultRootframe(frame->display),
                                         width, height,
                                         XDefaultDepth(frame->display,
                                                       frame->default_screen));

       if (frame->screen[i] == 0)
       {
         return NULL;
       }
     } */

    b_set_events(frame);

    /* frame->components = frame_queue();

     if (frame->components == NULL)
     {
       XCloseDisplay(frame->display);
       free(frame);
       return NULL;
     } */
  }

  return frame;
}



void b_open_frame(struct b_frame * const frame)
{
  XEvent event;

  XMapWindow(frame->display, frame->window);

  /* Waiting for expose event. */
  do
  {
    XNextEvent(frame->display, &event);
  }
  while (event.type != Expose);
}



Display * b_get_display(const struct b_frame * const frame)
{
  return frame->display;
}



Window b_get_window(const struct b_frame * const frame)
{
  return frame->window;
}



GC b_get_gc(const struct b_frame * const frame)
{
  return frame->graphics_context;
}



Atom b_get_close_operation(const struct b_frame * const frame)
{
  return frame->close_operation;
}



void b_add_component(struct b_frame * const frame,
                     b_component_s  * const component)
{
  b_set_frame(component, frame);
  b_draw_component(component);
}



void b_close_frame(struct b_frame * const frame)
{
  XUnmapWindow(frame->display, frame->window);
  XCheckTypedWindowEvent(frame->display, frame->window, UnmapNotify, NULL);
}



void b_destroy_frame(struct b_frame * const frame)
{
  XCloseDisplay(frame->display);
  free(frame);
}
