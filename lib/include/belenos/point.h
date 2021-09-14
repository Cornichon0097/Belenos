#ifndef _B_POINT_H
#define _B_POINT_H

#include <X11/Xlib.h>


typedef XPoint b_point_s;



void b_set_point(b_point_s * point, short x, short y);

void b_set_x(b_point_s * point, short x);

short b_get_x(const b_point_s * const point);

void b_set_y(b_point_s * point, short y);

short b_get_y(const b_point_s * const point);


#endif /* point.h */
