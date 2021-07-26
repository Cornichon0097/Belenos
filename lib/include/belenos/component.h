#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <belenos/color.h>
#include <belenos/window.h>


typedef struct component component_s;

typedef void (* drawer_t)(const component_s * const);
typedef void (* destroyer_t)(component_s * const);


struct component
{
  window_s  * window;
  int         x;
  int         y;
  color_t     color;
  drawer_t    drawer;
  destroyer_t destroyer;
};



component_s * new_component(const int x, const int y, const color_t color);

void set_component(struct component * const component, const int x, const int y, const color_t color);

void set_window(component_s * const component, window_s * const window);

void set_drawer(component_s * const component, const drawer_t drawer);

void draw_component(const component_s * const component);

void set_destroyer(component_s * const component, const destroyer_t destroyer);

void destroy_component(component_s * const component);


#endif /* component.h */
