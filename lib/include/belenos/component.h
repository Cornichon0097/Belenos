#ifndef _B_COMPONENT_H
#define _B_COMPONENT_H

#include <belenos/frame.h>
#include <belenos/point.h>
#include <belenos/color.h>


typedef struct b_component b_component_s;

typedef void (* b_drawer_t)    (const b_component_s *);
typedef void (* b_destroyer_t) (b_component_s *);


struct b_component
{
  b_point_s     coordinates;
  b_color_t     color;
  b_frame_s   * frame;
  b_drawer_t    drawer;
  b_destroyer_t destroyer;
};



b_component_s * b_new_component(short x, short y, b_color_t color);

void b_set_component(struct b_component * const component, short x, short y, b_color_t color);

void b_set_frame(b_component_s * const component, b_frame_s * frame);

void b_set_drawer(b_component_s * const component, b_drawer_t drawer);

void b_draw_component(const b_component_s * const component);

void b_set_destroyer(b_component_s * const component, b_destroyer_t destroyer);

void b_destroy_component(b_component_s * component);


#endif /* component.h */
