#include <stdlib.h>
#include <stdio.h>

#include <belenos/frame.h>
#include <belenos/event.h>

#define X 200
#define Y 100

#define WIDTH  500U
#define HEIGHT 300U



int main(void)
{
  b_frame_s * frame = b_new_frame(X, Y, WIDTH, HEIGHT);

  b_show_frame(frame);

  while (b_is_open(frame)) {}

  b_destroy_frame(frame);

  return EXIT_SUCCESS;
}
