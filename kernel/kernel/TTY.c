#include <kernel/TTY.h>
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (u16*) 0xB8000;
	for (ust y = 0; y < VGA_HEIGHT; y++) {
		for (ust x = 0; x < VGA_WIDTH; x++) {
			const ust index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(u8 color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, u8 color, ust x, ust y) 
{
	const ust index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	if(c == '\n')
	{
		terminal_row++;
		terminal_column=2;
	}else{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}
	}
}
 
void terminal_write(const char* data, ust size) 
{
	for (ust i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void drawWindow()
{
	terminal_putchar(218);
	for(int i = 0; i < 33; i++)
		terminal_putchar(196);
	terminal_putchar(180);
	u8 temptc = terminal_color;
	terminal_writestring(" Lilak OS ");
	terminal_putchar(195);
	for(int i = 0; i < 33; i++)
		terminal_putchar(196);
	terminal_putchar(191);
	for(int y = 0; y < 23; y++)
	{
		terminal_putchar(179);
		for(int x = 0; x < 78; x++)
			terminal_putchar(' ');
		terminal_putchar(179);
	}
	terminal_putchar(192);
	for(int x = 0; x < 78; x++)
		terminal_putchar(196);
	terminal_putchar(217);
	terminal_row = 1;
	terminal_column = 2;
}