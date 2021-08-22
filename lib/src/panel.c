#include <stdlib.h>

#include <belenos/color.h>
#include <belenos/draw.h>
#include <belenos/frame.h>
#include <belenos/component.h>
#include <belenos/panel.h>



b_panel_s * b_new_panel(const short          x,
                        const short          y,
                        const unsigned short width,
                        const unsigned short height,
                        const b_color_t      color)
{
  struct b_panel * panel;

  panel = (struct b_panel *) malloc(sizeof(struct b_panel));

  if (panel)
  {
    b_set_panel(panel, x, y, color, width, height);
    b_set_drawer((b_component_s *) panel, &b_draw_panel);
    b_set_destroyer((b_component_s *) panel, &b_destroy_panel);
  }

  return (b_panel_s *) panel;
}



void b_set_panel(struct b_panel * const panel,
                 const short            x,
                 const short            y,
                 const b_color_t        color,
                 const unsigned short   width,
                 const unsigned short   height)
{
  b_set_component((b_component_s *) panel, x, y, color);
  panel->width  = width;
  panel->height = height;
}



void b_draw_panel(const b_panel_s * const panel)
{
  b_fill_rectangle(panel->frame,
                   b_get_x(panel->coordinates), b_get_y(panel->coordinates),
                   ((struct b_panel *) panel)->width,
                   ((struct b_panel *) panel)->height,
                   panel->color);
}



void b_destroy_panel(b_panel_s * const panel)
{
  free(panel);
}
