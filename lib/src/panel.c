#include <stdlib.h>

#include <belenos/color.h>
#include <belenos/window.h>
#include <belenos/component.h>
#include <belenos/panel.h>



panel_s * new_panel(const int          x,
                    const int          y,
                    const unsigned int width,
                    const unsigned int height,
                    const color_t      color)
{
  struct panel * panel;

  panel = (struct panel *) malloc(sizeof(struct panel));

  if (panel)
  {
    set_panel(panel, x, y, color, width, height);
    set_drawer((component_s *) panel, &draw_panel);
    set_destroyer((component_s *) panel, &destroy_panel);
  }

  return (panel_s *) panel;
}



void set_panel(struct panel * const panel,
               const int                x,
               const int                y,
               const color_t            color,
               const unsigned int       width,
               const unsigned int       height)
{
  set_component((component_s *) panel, x, y, color);
  panel->width  = width;
  panel->height = height;
}



void draw_panel(const panel_s * const panel)
{
  XSetForeground(get_display(panel->window), get_gc(panel->window),
                 panel->color);
  XFillRectangle(get_display(panel->window), get_window(panel->window),
                 get_gc(panel->window), panel->x, panel->y,
                 ((struct panel *) panel)->width,
                 ((struct panel *) panel)->height);
  XFlush(get_display(panel->window));
}



void destroy_panel(panel_s * const panel)
{
  free(panel);
}
