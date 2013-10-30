#include "screen.h"
#include "portio.h"

static uint16_t *const video_memory = (uint16_t *) 0xB8000;

static const uint8_t ROWS = 25;
static const uint8_t COLS = 80;
static uint8_t  cursor_x = 0;
static uint8_t cursor_y = 0;

static color_t foreground_color = WHITE;
static color_t background_color = BLACK;

static void set_video_mem_char(uint8_t row, uint8_t col, char c);
static void set_video_mem(uint8_t row, uint8_t col, uint16_t data);
static void move_cursor(void);
static void draw_cursor(void);
static void scroll(void);

static void set_video_mem_char(uint8_t row, uint8_t col, char c) {
    uint8_t color = background_color << 4 | foreground_color;
    uint16_t entry = color << 8 | c;
    video_memory[row * COLS + col] = entry;
}

static void set_video_mem(uint8_t row, uint8_t col, uint16_t data) {
    video_memory[row * COLS + col] = data;
}

static uint16_t get_video_mem(uint8_t row, uint8_t col) {
    return video_memory[row * COLS + col];
}

static void move_cursor(void) {
    cursor_x++;
    if (cursor_x == COLS) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y == ROWS) {
        cursor_y--;
        scroll();
    }
}

static void draw_cursor(void) {
    uint16_t pos = cursor_y * COLS + cursor_x;
    outb(0x3D4, 15);
    outb(0x3D5, pos);
    outb(0x3D4, 14);
    outb(0x3D5, pos >> 8);
}

static void scroll(void) {
    // Shift all rows up by one
    int i, j;
    for (i = 1; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            set_video_mem(i - 1, j, get_video_mem(i, j));
        }
    }

    // Clear the last row
    for (i = 0; i < COLS; i++) {
        set_video_mem_char(ROWS - 1, i, ' ');
    }
}

void cls(void) {
    int i, j;
    for (i = 0; i < COLS; i++) {
        for (j = 0; j < ROWS; j++) {
            set_video_mem_char(j, i, ' ');
        }
    }
    cursor_x = 0;
    cursor_y = 0;
    draw_cursor();
}

void putchar(const char c) {
    switch(c) {
    case '\n':
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= ROWS) {
            cursor_y--;
            scroll();
        }
        break;
    case '\r':
        cursor_x = 0;
        break;
    default:
        set_video_mem_char(cursor_y, cursor_x, c);
        move_cursor();
    }
    draw_cursor();
}

void puts(const char *string) {
    while (*string) {
        putchar(*string++);
    }
}

void puti(int n) {
    if (n >= 10) {
        puti(n / 10);
    }
    putchar('0' + n % 10);
}

void set_text_color(color_t fg_color, color_t bg_color) {
    foreground_color = fg_color;
    background_color = bg_color;
}
