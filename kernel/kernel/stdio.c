#include <kernel/stdio.h>
#include <kernel/TTY.h>
#include <kernel/stdarg.h>
#include <kernel/system.h>

int printf(const char* restrict format, ...)
{
    va_list parameters;
    va_start(parameters, format);
    while(*format)
    {
        if(*format == '%')
        {
            format++;
            switch(*format)
            {
                case 'c':
                    format++;
                    char c = (char) va_arg(parameters, int);
                    terminal_putchar(c);
                    break;
                case 's':
                    format++;
                    const char* str = va_arg(parameters, const char*);
                    terminal_writestring(str);
                    break;
                case 'i':
                    format++;
                    int i = va_arg(parameters, unsigned int);
                    char* o;
                    itoa(i, 10, o);
                    terminal_writestring(o);
                    break;
                case 'x':
                    format++;
                    int xi = va_arg(parameters, unsigned int);
                    char* xo;
                    itoa(xi, 16, xo);
                    terminal_writestring("0x");
                    terminal_writestring(xo);
                    terminal_column--;
                    terminal_putchar(' ');
                    break;
            }
        }
        terminal_putchar(*format);
        format++;
    }
}