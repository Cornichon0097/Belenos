#include <belenos/draw.h>



void b_draw_point(const b_frame_s * const frame,
                  const int               x,
                  const int               y,
                  const b_color_t         color)
{
  XSetForeground(b_get_display(frame), b_get_gc(frame), color);
  XDrawPoint(b_get_display(frame), b_get_window(frame), b_get_gc(frame), x, y);
  XFlush(b_get_display(frame));
}



void b_draw_line(const b_frame_s * const frame,
                 const int               x1,
                 const int               y1,
                 const int               x2,
                 const int               y2,
                 const b_color_t         color)
{
  XSetForeground(b_get_display(frame), b_get_gc(frame), color);
  XDrawLine(b_get_display(frame), b_get_window(frame), b_get_gc(frame),
            x1, y1, x2, y2);
  XFlush(b_get_display(frame));
}



void b_draw_rectangle(const b_frame_s * const frame,
                      const int               x,
                      const int               y,
                      const unsigned int      width,
                      const unsigned int      height,
                      const b_color_t         color)
{
  XSetForeground(b_get_display(frame), b_get_gc(frame), color);
  XDrawRectangle(b_get_display(frame), b_get_window(frame), b_get_gc(frame),
                 x, y, width, height);
  XFlush(b_get_display(frame));
}



void b_draw_arc(const b_frame_s * const frame,
                 const int               x,
                 const int               y,
                 const unsigned int      width,
                 const unsigned int      height,
                 const int               angle1,
                 const int               angle2,
                 const b_color_t         color)
{
  XSetForeground(b_get_display(frame), b_get_gc(frame), color);
  XDrawArc(b_get_display(frame), b_get_window(frame), b_get_gc(frame),
           x, y, width, height, angle1, angle2);
  XFlush(b_get_display(frame));
}



void b_fill_rectangle(const b_frame_s * const frame,
                      const int               x,
                      const int               y,
                      const unsigned int      width,
                      const unsigned int      height,
                      const b_color_t         color)
{
  XSetForeground(b_get_display(frame), b_get_gc(frame), color);
  XFillRectangle(b_get_display(frame), b_get_window(frame), b_get_gc(frame),
                 x, y, width, height);
  XFlush(b_get_display(frame));
}



void b_fill_arc(const b_frame_s * const frame,
                 const int               x,
                 const int               y,
                 const unsigned int      width,
                 const unsigned int      height,
                 const int               angle1,
                 const int               angle2,
                 const b_color_t         color)
{
  XSetForeground(b_get_display(frame), b_get_gc(frame), color);
  XFillArc(b_get_display(frame), b_get_window(frame), b_get_gc(frame),
           x, y, width, height, angle1, angle2);
  XFlush(b_get_display(frame));
}



void b_fill_polygon(const b_frame_s * frame, b_point_s * const points, int nb_points, b_color_t color)
{
  XSetForeground(b_get_display(frame), b_get_gc(frame), color);
  XFillPolygon(b_get_display(frame), b_get_window(frame), b_get_gc(frame),
               points, nb_points, Complex, CoordModeOrigin);
  XFlush(b_get_display(frame));
}
