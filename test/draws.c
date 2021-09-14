#include <stdlib.h>
#include <stdio.h>

#include <belenos/frame.h>
#include <belenos/point.h>
#include <belenos/color.h>
#include <belenos/draw.h>
#include <belenos/event.h>

#define X 200
#define Y 100

#define WIDTH  500U
#define HEIGHT 300U

#define TRIANGLE_NB_POINTS 3



int main(void)
{
  b_frame_s * frame = b_new_frame(X, Y, WIDTH, HEIGHT);

  b_point_s triangle_points[TRIANGLE_NB_POINTS] =
  {
    {WIDTH / 2,     HEIGHT / 2},
    {WIDTH / 3,     HEIGHT},
    {2 * WIDTH / 3, HEIGHT}
  };

  b_show_frame(frame);

  b_draw_line(frame, 0, (HEIGHT / 2), WIDTH, (HEIGHT / 2), BLUE);
  b_fill_rectangle(frame, 0, 0, 100, 100, b_rgb(255, 0, 0));
  b_draw_arc(frame, 300, 0, 100, 100, 0, 360, 0x00FF00);
  b_fill_polygon(frame, triangle_points, TRIANGLE_NB_POINTS, PURPLE);

  while (b_is_open(frame)) {}

  b_destroy_frame(frame);

  return EXIT_SUCCESS;
}
