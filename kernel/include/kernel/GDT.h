#include <types.h>

#define SEGPRESENT 0x80
#define SEGNOTPRESENT 0x00
#define PRIVILEGELEVEL0 0x00
#define PRIVILEGELEVEL1 0X20
#define PRIVILEGELEVEL2 0x40
#define PRIVILEGELEVEL3 0x60

#define DATARD 0x00
#define DATARDA 0x01
#define DATARDWR 0x02
#define DATARDWRA 0x03
#define DATARDEXPD 0x04
#define DATARDEXPDA 0x05
#define DATARDWREXPD 0x06
#define DATARDWREXPDA 0x07

#define CODEEX 0x08
#define CODEEXA 0x09
#define CODEEXRD 0x0A
#define CODEEXRDA 0x0B
#define CODEEXC 0x0C
#define CODEEXCA 0x0D
#define CODEEXRDC 0x0E
#define CODEEXRDCA 0xF

#define PROTECTIONLEVEL0CODE SEGPRESENT | PRIVILEGELEVEL0 | CODEDATA | CODEEXRD
#define PROTECTIONLEVEL0DATA SEGPRESENT | PRIVILEGELEVEL0 | CODEDATA | DATARDWR

#define PROTECTIONLEVEL3CODE SEGPRESENT | PRIVILEGELEVEL3 | CODEDATA | CODEEXRD
#define PROTECTIONLEVEL3DATA SEGPRESENT | PRIVILEGELEVEL3 | CODEDATA | DATARDWR

#define BYTEGRANULARITY 0x00
#define KILOBYTEGRANULARITY 0x80
#define SIXTEENBITOPSIZE 0x00
#define THIRTYTWOBITOPSIZE 0x40
#define ZERO 0x00
#define CODEDATA 0x10
#define SYSTEM 0x00

#define STANDARDGRANULARITYBYTE KILOBYTEGRANULARITY | THIRTYTWOBITOPSIZE | 0x0F

extern void FlushGDT(u32);

struct GDTEntry_s
{
    u16 LimitLow;
    u16 BaseLow;
    u8 BaseMiddle;
    u8 flags;
    u8 granularity;
    u8 BaseHigh;
};

typedef struct GDTEntry_s GDTEntry_t;
typedef struct GDTPointer_s GDTPointer_t;

GDTEntry_t GDTEntries[5];
u64 GDTPointer;

GDTEntry_t MakeDescriptor(u32 base, u32 limit, u8 flags,u8 granularity)
{
    GDTEntry_t ret;
    ret.BaseLow = (base & 0xFFFF);
    ret.BaseMiddle = (base >> 16) & 0xFF;
    ret.BaseHigh = (base >> 24) & 0xFF;

    ret.LimitLow = (limit & 0xFFFF);
    ret.granularity = (limit >> 16) & 0x0F;
    ret.granularity |= granularity & 0xF0;
    
    ret.flags = flags;

    return ret;
}

void StandardGlobalDescriptorSetup()
{
    GDTPointer = (u32) &GDTEntries;
    GDTPointer <<= 16;
    GDTPointer |= (u16) (sizeof(GDTEntry_t)*5)-1;
    
    GDTEntries[0] = MakeDescriptor(0, 0, 0, 0);
    GDTEntries[1] = MakeDescriptor(0x00000000, 0xFFFFFFFF, PROTECTIONLEVEL0CODE, STANDARDGRANULARITYBYTE);
    GDTEntries[2] = MakeDescriptor(0x00000000, 0xFFFFFFFF, PROTECTIONLEVEL0DATA, STANDARDGRANULARITYBYTE);
    GDTEntries[3] = MakeDescriptor(0x00000000, 0xFFFFFFFF, PROTECTIONLEVEL3CODE, STANDARDGRANULARITYBYTE);
    GDTEntries[4] = MakeDescriptor(0x00000000, 0xFFFFFFFF, PROTECTIONLEVEL3DATA, STANDARDGRANULARITYBYTE);

    FlushGDT((u32)&GDTPointer);
}