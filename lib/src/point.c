#include <belenos/point.h>



void b_set_point(b_point_s * point,
                 const short x,
                 const short y)
{
  point->x = x;
  point->y = y;
}



void b_set_x(b_point_s * const point,
             const short       x)
{
  point->x = x;
}



short b_get_x(const b_point_s * const point)
{
  return point->x;
}



void b_set_y(b_point_s * const point,
             const short       y)
{
  point->y = y;
}



short b_get_y(const b_point_s * const point)
{
  return point->y;
}
