#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <stdint.h>

typedef enum {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHT_GREY, DARK_GREY,
	LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_MAGENTA, YELLOW,
	WHITE
} color_t;

/** Clears the screen */
void cls(void);

/** Puts a character on the screen */
void putchar(char c);

/** Puts a string on the screen */
void puts(char *str);

/** Sets the text color */
void set_text_color(color_t fg_color, color_t bg_color);

#endif
