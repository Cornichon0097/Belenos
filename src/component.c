#include <stdlib.h>

#include <X11/Xlib.h>

#include <belenos/color.h>
#include <belenos/window.h>
#include <belenos/component.h>



component_s * new_component(const int     x,
                            const int     y,
                            const color_t color)
{
  struct component * component;

  component = (struct component *) malloc(sizeof(struct component));

  if (component)
  {
    set_component(component, x, y, color);
    set_drawer(component, NULL);
    set_destroyer(component, NULL);
  }

  return component;
}



void set_component(struct component * const component,
                   const int                x,
                   const int                y,
                   const color_t            color)
{
  component->window    = NULL;
  component->x         = x;
  component->y         = y;
  component->color     = color;
}



void set_window(component_s * const component,
                window_s    * const window)
{
  if (component)
  {
    component->window = window;
  }
}



void set_drawer(component_s * const component,
                const drawer_t      drawer)
{
  if (component)
  {
    component->drawer = drawer;
  }
}



void draw_component(const component_s * const component)
{
  if (component)
  {
    if (component->drawer)
    {
      component->drawer(component);
    }
  }
}



void set_destroyer(component_s * const component,
                   const destroyer_t   destroyer)
{
  if (component)
  {
    component->destroyer = destroyer;
  }
}



void destroy_component(component_s * const component)
{
  if (component)
  {
    /* If the destroyer is set, then it is called. The destroyer
     * must destroy everything, including the component itself.
     */
    if (component->destroyer)
    {
      component->destroyer(component);
    }
    /* If the destroyer is not set, then the component is probably a
     * basic component. If it is, a simple free() call will destroy it.
     */
    else
    {
      free(component);
    }
  }
}
