#include <types.h>
#include <TTY.h>
#include <GDT.h>
#include <Multiboot.h>

extern char* CPUInfo();
struct multibootHeader mb;
char l[32];

void DisplayHardwareInfo();

void CKernelFunction(struct multibootHeader* mbheader)
{
    mb = *mbheader;
    TTYClear();
    TTYWriteString("Lilak OS v1.0\n");
    char* blname = (char*) mb.BootloaderName;
    TTYWriteString("Booted from ");
    TTYWriteString(blname);
    TTYPutc('\n');
    StandardGlobalDescriptorSetup();
    TTYWriteString("GDT Installed\n");
    DisplayHardwareInfo();
    for(;;);
}

void DisplayHardwareInfo(){
    TTYWriteString("Hardware info:\n     CPU: ");
    CPUInfo();
    TTYColor = 0x0F;
    TTYWriteString("\n     RAM size: 0x");
    itoax(mb.HighMem, 16, l);
    TTYWriteString(l);
    TTYWriteString(" bytes");
}
