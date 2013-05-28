#include "screen.h"
#include "portio.h"

static const uint8_t ROWS = 25;
static const uint8_t COLS = 80;
static uint8_t  cursor_x = 0;
static uint8_t cursor_y = 0;

static color_t foreground_color = WHITE;
static color_t background_color = BLACK;

static void set_video_mem(uint8_t row, uint8_t col, char c);
static void move_cursor();
static void draw_cursor();

static void set_video_mem(uint8_t row, uint8_t col, char c) {
	static uint16_t *video_memory = (uint16_t *) 0xB8000;
	uint8_t color = background_color << 4 | foreground_color;
	uint16_t entry = color << 8 | c;
	video_memory[row * COLS + col] = entry;
}

static void move_cursor() {
	cursor_x++;
	if (cursor_x == COLS) {
		cursor_x = 0;
		cursor_y++;
	}
	if (cursor_y == ROWS) {
		cursor_y--;
		int i;
		for (i = 0; i < COLS; i++) {
			set_video_mem(cursor_y, i, ' ');
		}
	}
}

static void draw_cursor() {
	uint16_t pos = cursor_y * COLS + cursor_x;
	outb(0x3D4, 15);
	outb(0x3D5, pos);
	outb(0x3D4, 14);
	outb(0x3D5, pos >> 8);
}

void cls() {
	int i, j;
	for (i = 0; i < COLS; i++) {
		for (j = 0; j < ROWS; j++) {
			set_video_mem(j, i, ' ');
		}
	}
	cursor_x = 0;
	cursor_y = 0;
	draw_cursor();
}

void putchar(char c) {
	switch(c) {
	case '\n':
		cursor_x = 0;
		cursor_y++;
		break;
	case '\r':
		cursor_x = 0;
		break;
	default:
		set_video_mem(cursor_y, cursor_x, c);
		move_cursor();
	}
	draw_cursor();
}

void puts(char *string) {
	while (*string) {
		putchar(*string++);
	}
}

void set_text_color(color_t fg_color, color_t bg_color) {
	foreground_color = fg_color;
	background_color = bg_color;
}
