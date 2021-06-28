#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include <belenos/color.h>
#include <belenos/window.h>
#include <belenos/component.h>


typedef component_s panel_s;

struct panel
{
  component_s  super;
  unsigned int width;
  unsigned int height;
};



panel_s * new_panel(const int x, const int y, const unsigned int width, const unsigned int height, const color_t color);

void set_panel(struct panel * const panel, const int x, const int y, const color_t color, const unsigned int width, const unsigned int height);

void draw_panel(const panel_s * const panel);

void destroy_panel(panel_s * const panel);


#endif /* panel.h */
