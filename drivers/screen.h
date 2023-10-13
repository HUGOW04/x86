#ifndef SCREEN_H
#define SCREEN_H

#include "../cpu/type.h"

#define BLACK   0x00
#define BLUE    0x10
#define GREEN   0x20
#define CYAN    0x30
#define RED     0x40
#define MAGENTA 0x50
#define BROWN   0x60
#define LIGHT_GRAY  0x70
#define DARK_GRAY   0x80
#define LIGHT_BLUE  0x90
#define LIGHT_GREEN 0xA0
#define LIGHT_CYAN  0xB0
#define LIGHT_RED   0xC0
#define LIGHT_MAGENTA 0xD0
#define YELLOW      0xE0
#define WHITE       0xF0

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

extern int background_color;

/* Public kernel API */
void clear_screen();
void kprint_at(char *message, int col, int row);
void kprint(char *message);
void kprint_backspace();

#endif
