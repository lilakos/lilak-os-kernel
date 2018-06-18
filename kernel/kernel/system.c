#include <kernel/system.h>

char tbuffer[32];
char bchars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void itoa(u32 interger, ust base, char* buf)
{
    int position;
    int oposition;
    int top;

    if(interger == 0 || base > 16){
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    while(interger!=0)
    {
        tbuffer[position] = bchars[interger % base];
        position++;
        interger /= base;
    }
    top = position--;
    for(oposition=0; oposition<top; position--, oposition++)
    {
        buf[oposition] = tbuffer[position];
    }
    buf[oposition] = 0;
}