#include <stdlib.h>
#include <stdio.h>

#include <belenos/color.h>
#include <belenos/window.h>
#include <belenos/event.h>
#include <belenos/panel.h>

#define X 200
#define Y 100

#define WIDTH  500U
#define HEIGHT 300U



int main(void)
{
  window_s * window = new_window(X, Y, WIDTH, HEIGHT);
  panel_s  * panel  = new_panel(0, 0, 100, 100, rgb(255, 0, 0));

  open_window(window);

  add_component(window, panel);

  while (is_open(window)) {}

  /* close_window(window); */

  destroy_component(panel);
  destroy_window(window);

  return EXIT_SUCCESS;
}
