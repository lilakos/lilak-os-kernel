#include <kernel/types.h>
#include <kernel/VGA.h>
#include <kernel/string.h>
#include <kernel/TTY.h>
#include <kernel/stdio.h>

#define SUCCESSCOLOR 0xAF
#define FAILCOLOR 0xCF

void kernel_main() 
{
	terminal_initialize();
	drawWindow();
	terminal_writestring("LilakOS v0.01\n");
    printf("Hello, World!,\nThe leter C: %c\nThe letter D: %c\nThe sentence \"Hello, World!\": %s\n", 'C', 'D', "Hello, World!");
    printf("The number 512 in base 10: %i\n", 512);
    printf("The number 512 in base 16: %x\n", 512);
    printf("printf(char* format, ...);");
}