#include <types.h>

/*
 * ISR0 = Division by zero
 * ISR1 = Debug
 * ISR2 = NMI
 * ISR3 = Breakpoint Exception
 * ISR4 = Into detected overflow
 * ISR5 = Out of bounds
 * ISR6 = Invalid opcode
 * ISR7 = No coprocessor
 * ISR8 = Double fault
 * ISR9 = Coprocessor Segment overrun
 * ISR10 = Bad TSS
 * ISR11 = Segment not present
 * ISR12 = Stack fault
 * ISR13 = General fault
 * ISR14 = Page fault
 * ISR15 = Unknown interrupt
 * ISR16 = Coprocessor fault
 * ISR17 = Alignment check
 * ISR18 = Machine check
 * ISR19 = Reserved
 * ISR20 = Reserved
 * ISR21 = Reserved
 * ISR22 = Reserved
 * ISR23 = Reserved
 * ISR24 = Reserved
 * ISR25 = Reserved
 * ISR26 = Reserved
 * ISR27 = Reserved
 * ISR28 = Reserved
 * ISR29 = Reserved
 * ISR30 = Reserved
 * ISR31 = Reserved
*/

/*
 *
 * IRQ0 = PIT
 * IRQ1 = Keyboard
 * IRQ2 = Cascade
 * IRQ3 = COM2
 * IRQ4 = COM1
 * IRQ5 = LPT2
 * IRQ6 = Floppy disk controller
 * IRQ7 = LPT1
 * IRQ8 = CMOS realtime clock
 * IRQ9 = Free for peripherals / Legacy SCSI / NIC
 * IRQ10 = Free for peripherals / SCSI / NIC
 * IRQ11 = Free for peripherals / SCSI / NIC
 * IRQ12 = PS/2 Mouse
 * IRQ13 = Floating Point Unit / Coprocessor / Inter-processor
 * IRQ14 = Primary ATA Hard Disk
 * IRQ15 = Secondary ATA Hard Disk
 *
*/

#define PRESENT 0x80
#define PRIVILEGELEVEL0 0x00
#define PRIVILEGELEVEL1 0X20
#define PRIVILEGELEVEL2 0x40
#define PRIVILEGELEVEL3 0x60
#define SPECIAL 0xC

#define STANDARDFLAGSBYTE PRESENT | PRIVILEGELEVEL0 | SPECIAL

struct IDTEntry {
    u16 low;
    u16 selector;
    u8 zero = 0;
    u8 flags;
    u16 high;
};


