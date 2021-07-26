#include <stdlib.h>
#include <stdio.h>

#include <belenos/color.h>



/*
 * Returns hexadecimal color from red, green and blue parameters.
 */
color_t rgb(const unsigned char r, /* Red parameter.   */
            const unsigned char g, /* Green parameter. */
            const unsigned char b) /* Blue parameter.  */
{
  /* A hexadecimal color is specified with: #RRGGBB.
     RR (red), GG (green) and BB (blue) are hexadecimal integers
     between 00 and FF specifying the intensity of the color.
   */
  return (color_t) ((r << 16) | (g << 8) | b);
}
