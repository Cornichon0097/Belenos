#ifndef _WINDOW_H
#define _WINDOW_H

#include <X11/Xlib.h>
#include <X11/Xatom.h>


/*
 * Window structure type definition.
 */
typedef struct window window_s;


#include <belenos/component.h>



struct window * new_window(const int x, const int y, const unsigned int width, const unsigned int height);

void open_window(struct window * const window);

Display * get_display(const struct window * const window);

Window get_window(const struct window * const window);

GC get_gc(const struct window * const window);

Atom get_close_operation(const struct window * const window);

void add_component(struct window * const window, component_s * const component);

void close_window(struct window * const window);

void destroy_window(struct window * const window);


#endif /* window.h */
