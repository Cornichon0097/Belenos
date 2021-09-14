#include <stdlib.h>

#include <belenos/frame.h>
#include <belenos/component.h>



b_component_s * b_new_component(const short     x,
                                const short     y,
                                const b_color_t color)
{
  struct b_component * component;

  component = (struct b_component *) malloc(sizeof(struct b_component));

  if (component)
  {
    b_set_component(component, x, y, color);
    b_set_drawer(component, NULL);
    b_set_destroyer(component, NULL);
  }

  return component;
}



void b_set_component(struct b_component * const component,
                     const short                x,
                     const short                y,
                     const b_color_t            color)
{
  b_set_point(&(component->coordinates), x, y);
  component->frame = NULL;
  component->color = color;
}



void b_set_frame(b_component_s * const component,
                 b_frame_s     * const frame)
{
  if (component)
  {
    component->frame = frame;
  }
}



void b_set_drawer(b_component_s * const component,
                  const b_drawer_t      drawer)
{
  if (component)
  {
    component->drawer = drawer;
  }
}



void b_draw_component(const b_component_s * const component)
{
  if (component)
  {
    if (component->drawer)
    {
      component->drawer(component);
    }
  }
}



void b_set_destroyer(b_component_s * const component,
                     const b_destroyer_t   destroyer)
{
  if (component)
  {
    component->destroyer = destroyer;
  }
}



void b_destroy_component(b_component_s * const component)
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
