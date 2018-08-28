#include <types.h>

extern char* CPUInfo();
char l[32];

void DisplayHardwareInfo(u32 RAMSize)
{
    TTYWriteString("Hardware info:\n     CPU: ");
    CPUInfo();
    TTYColor = 0x0F;
    TTYWriteString("\n     RAM: 0x");
    itoax(RAMSize, 16, l);
    TTYWriteString(l);
    TTYWriteString(" bytes");
}