#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <belenos/window.h>
#include <belenos/component.h>

#define BORDERWIDTH 1U


struct window
{
  Display * display;
  int       default_screen;
  Window    window;
  GC        graphics_context;
  Atom      close_operation;
};



static int create_window(struct window * const window,
                         const int               x,
                         const int               y,
                         const unsigned int      width,
                         const unsigned int      height)
{
  window->window = XCreateSimpleWindow(window->display,
                                       XRootWindow(window->display,
                                                   window->default_screen),
                                       x, y, width, height, BORDERWIDTH,
                                       XBlackPixel(window->display,
                                                   window->default_screen),
                                       XWhitePixel(window->display,
                                                   window->default_screen));

  if (window->window == 0UL)
  {
    return 0;
  }

  return 1;
}



static int set_hints(struct window * const window,
                     const int               x,
                     const int               y)
{
  XSizeHints * hints = XAllocSizeHints();

  if (hints == NULL)
  {
    return 0;
  }

  hints->flags = PPosition;
  hints->x     = x;
  hints->y     = y;

  XSetWMNormalHints(window->display, window->window, hints);
  XFree(hints);

  return 1;
}



static int set_graphic(struct window * const window,
                       const int               x,
                       const int               y,
                       const unsigned int      width,
                       const unsigned int      height)
{
  window->default_screen   = XDefaultScreen(window->display);
  window->graphics_context = XDefaultGC(window->display,
                                        window->default_screen);

  return (create_window(window, x, y, width, height)
          && set_hints(window, x, y));
}



static void set_events(struct window * const window)
{
  XSetWindowAttributes attributes;

  XSelectInput(window->display, window->window, ExposureMask
                                              | KeyPressMask
                                              | KeyReleaseMask
                                              | ButtonPressMask
                                              | ButtonReleaseMask
                                              | StructureNotifyMask);

  attributes.backing_store = Always;
  XChangeWindowAttributes(window->display, window->window,
                          CWBackingStore, &attributes);

  window->close_operation = XInternAtom(window->display,
                                        "WM_DELETE_WINDOW", False);
  XSetWMProtocols(window->display, window->window,
                  &(window->close_operation), 1);
}



struct window * new_window(const int          x,
                           const int          y,
                           const unsigned int width,
                           const unsigned int height)
{
  struct window * window;

  window = (struct window *) malloc(sizeof(struct window));

  if (window)
  {
    window->display = XOpenDisplay(NULL);

    if (window->display == NULL)
    {
      free(window);
      return NULL;
    }

    if (!set_graphic(window, x, y, width, height))
    {
      destroy_window(window);
      return NULL;
    }

    /* Multiple screens, for later. */
    /* for (size_t i = 1; i < NB_SCREENS; i++)
     {
       window->screen[i] = XCreatePixmap(window->display,
                                         XDefaultRootWindow(window->display),
                                         width, height,
                                         XDefaultDepth(window->display,
                                                       window->default_screen));

       if (window->screen[i] == 0)
       {
         return NULL;
       }
     } */

    set_events(window);

    /* window->components = window_queue();

     if (window->components == NULL)
     {
       XCloseDisplay(window->display);
       free(window);
       return NULL;
     } */
  }

  return window;
}



void open_window(struct window * const window)
{
  XEvent event;

  XMapWindow(window->display, window->window);

  /* Waiting for expose event. */
  do
  {
    XNextEvent(window->display, &event);
  }
  while (event.type != Expose);
}



Display * get_display(const struct window * const window)
{
  return window->display;
}



Window get_window(const struct window * const window)
{
  return window->window;
}



GC get_gc(const struct window * const window)
{
  return window->graphics_context;
}



Atom get_close_operation(const struct window * const window)
{
  return window->close_operation;
}



void add_component(struct window    * const window,
                   struct component * const component)
{
  set_window(component, window);
  draw_component(component);
}



void close_window(struct window * const window)
{
  XUnmapWindow(window->display, window->window);
  XCheckTypedWindowEvent(window->display, window->window, UnmapNotify, NULL);
}



void destroy_window(struct window * const window)
{
  XCloseDisplay(window->display);
  free(window);
}
