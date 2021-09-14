#ifndef _B_DRAW_H
#define _B_DRAW_H

#include <belenos/frame.h>
#include <belenos/point.h>
#include <belenos/color.h>



void b_draw_point(const b_frame_s * frame, int x, int y, b_color_t color);

void b_draw_line(const b_frame_s * frame, int x1, int y1, int x2, int y2, b_color_t color);

void b_draw_rectangle(const b_frame_s * frame, int x, int y, unsigned int width, unsigned int height, b_color_t color);

void b_draw_arc(const b_frame_s * frame, int x, int y, unsigned int width, unsigned int height, int angle1, int angle2, b_color_t color);

void b_fill_rectangle(const b_frame_s * frame, int x, int y, unsigned int width, unsigned int height, b_color_t color);

void b_fill_arc(const b_frame_s * frame, int x, int y, unsigned int width, unsigned int height, int angle1, int angle2, b_color_t color);

void b_fill_polygon(const b_frame_s * frame, b_point_s * points, int nb_points, b_color_t color);


#endif /* draw.h */
