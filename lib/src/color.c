/*
 * Color C file.
 *
 * This file provides a rgb to hexadecimal color function. Colors used by
 * Belenos are hexadecimal colors, based on Xlib color system. This function
 * gives possibility to use rgb colors with Belenos.
 */

#include <belenos/color.h>



/*
 * Returns hexadecimal color from red, green and blue parameters.
 */
b_color_t b_rgb(const unsigned char r, /* Red parameter.   */
                const unsigned char g, /* Green parameter. */
                const unsigned char b) /* Blue parameter.  */
{
  /* A hexadecimal color is specified with: #RRGGBB.
     RR (red), GG (green) and BB (blue) are hexadecimal integers
     between 00 and FF specifying the intensity of the color.
   */
  return (b_color_t) ((r << 16) | (g << 8) | b);
}
