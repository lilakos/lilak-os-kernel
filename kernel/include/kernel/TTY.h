#pragma once
#include <types.h>

u8 TTYColor = 0x0F;
size_t TTYRow = 0;
size_t TTYColumn = 0;
u16* TTYMemory = (u16*) 0xB8000;

enum ColorPalette16{
    Black = 0x0,
    Blue = 0x1,
    Green = 0x2,
    Cyan = 0x3,
    Red = 0x4,
    Magenta = 0x5,
    Brown = 0x6,
    LightGrey = 0x7,
    DarkGrey = 0x8,
    LightBlue = 0x9,
    LightGreen = 0xA,
    LightCyan = 0xB,
    LightRed = 0xC,
    LightMagenta = 0xD,
    LightBrown = 0xE,
    White = 0xF
};

size_t strlen(const char* string)
{
    size_t ret = 0;
    while(string[ret])
        ret++;
    return ret;
}

char VGAMakeColor(enum ColorPalette16 fg, enum ColorPalette16 bg)
{
    return fg | bg << 4;
}

u16 VGAMakeEntry(char c, char color)
{
    return c | color << 8;
}

void VGASetColor(char color)
{
    TTYColor = color;
}

void TTYPutcat(char c, size_t x, size_t y)
{
    TTYMemory[y*80+x] = VGAMakeEntry(c, TTYColor);
}

void TTYPutc(char c)
{
    if(c == '\n')
    {
        TTYColumn = 0;
        TTYRow++;
    }else{
        TTYPutcat(c, TTYColumn, TTYRow);
        if(++TTYColumn == 80)
        {
            TTYColumn = 0;
            if(++TTYRow == 25)
                TTYRow = 0;
        }
    }
}

void TTYWrite(const char* data, size_t size)
{
    for(size_t i = 0; i < size; i++)
        TTYPutc(data[i]);
}

void TTYWriteString(const char* string)
{
    TTYWrite(string, strlen(string));
}

void TTYClear()
{
    TTYRow = 0;
    TTYColumn = 0;
    for(size_t y = 0; y < 25; y++)
    {
        for(size_t x = 0; x < 80; x++)
        {
            size_t i = y*80+x;
            TTYMemory[i] = VGAMakeEntry(0x00, TTYColor);
        }
    }
}
/*Interger to Ascii Hex*/
char hexchars[] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',   
};

char tbuffer[32] ;
void itoax(u32 number, unsigned base, char* buf)
{
    u32 pos = 0;
    u32 rpos = 0;
    u32 top = 0;

    if(number == 0)
    {
        buf[0] = '0';
        buf[1] = 0;
    }
    while(number!=0)
    {
        tbuffer[pos] = hexchars[number % base];
        pos++;
        number/=base;
    }
    top = pos--;

    for(rpos = 0; rpos < top; pos--, rpos++){
        buf[rpos] = tbuffer[pos];
    }

    buf[rpos] = 0x00;

}