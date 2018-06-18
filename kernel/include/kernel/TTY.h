#ifndef TTY_H
#define TTY_H

#include <kernel/VGA.h>
#include <kernel/types.h>
#include <kernel/string.h>


static const ust VGA_WIDTH = 80;
static const ust VGA_HEIGHT = 25;
 
ust terminal_row;
ust terminal_column;
u8 terminal_color;
u16* terminal_buffer;
 
void terminal_initialize(void);
void terminal_setcolor(u8 color);
void terminal_putentryat(char c, u8 color, ust x, ust y);
void terminal_putchar(char c);
void terminal_write(const char* data, ust size);
void terminal_writestring(const char* data);
void drawWindow();

#endif