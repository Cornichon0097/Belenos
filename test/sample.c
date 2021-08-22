#include <stdlib.h>
#include <stdio.h>

#include <belenos/color.h>
#include <belenos/frame.h>
#include <belenos/event.h>
#include <belenos/panel.h>

#define X 200
#define Y 100

#define WIDTH  500U
#define HEIGHT 300U



int main(void)
{
  b_frame_s * frame = b_new_frame(X, Y, WIDTH, HEIGHT);
  b_panel_s * panel = b_new_panel(0, 0, 100, 100, b_rgb(255, 0, 0));

  b_open_frame(frame);

  b_add_component(frame, panel);

  while (b_is_open(frame)) {}

  /* b_close_frame(frame); */

  b_destroy_component(panel);
  b_destroy_frame(frame);

  return EXIT_SUCCESS;
}
