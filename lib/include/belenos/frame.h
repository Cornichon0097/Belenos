/*
 * Frame header file.
 *
 * This header file provides the Belenos frame structure with the constructor,
 * the destroyer and some setters and getters.
 *
 * The Belenos frame can contain drawable Belenos components. Components in the
 * frmae appear only when the frame is open. Components can be added before or
 * after the frame is visible.
 */

#ifndef _B_FRAME_H
#define _B_FRAME_H

#include <X11/Xlib.h>
#include <X11/Xatom.h>


/*
 * Belenos frame structure type definition.
 * The Belenos frame structure is protected in the frame C file.
 */
typedef struct b_frame b_frame_s;


#include <belenos/component.h>



/*
 * The constructor.
 * Create a new width by height frame at coordonates x and y (position relative
 * to the upper left conner of the screen).
 */
b_frame_s * b_new_frame(int x, int y, unsigned int width, unsigned int height);

Display * b_get_display(const b_frame_s * frame);

Window b_get_window(const b_frame_s * frame);

GC b_get_gc(const b_frame_s * frame);

Atom b_get_close_operation(const b_frame_s * frame);

void b_add_component(b_frame_s * frame, b_component_s * component);

void b_show_frame(b_frame_s * frame);

void b_hide_frame(b_frame_s * frame);

void b_destroy_frame(b_frame_s * frame);


#endif /* frame.h */
