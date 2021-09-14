#ifndef _B_PANEL_H
#define _B_PANEL_H

#include <belenos/color.h>
#include <belenos/component.h>


typedef b_component_s b_panel_s;

struct b_panel
{
  b_component_s  super;
  unsigned short width;
  unsigned short height;
};



b_panel_s * b_new_panel(short x, short y, unsigned short width, unsigned short height, b_color_t color);

void b_set_panel(struct b_panel * panel, short x, short y, unsigned short width, unsigned short height, b_color_t color);

void b_draw_panel(const b_panel_s * panel);

void b_destroy_panel(b_panel_s * panel);


#endif /* panel.h */
