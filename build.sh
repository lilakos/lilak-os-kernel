cd Kernel
nasm -f elf32 boot.asm -o ../obj/Kernel/boot.o
nasm -f elf32 src/GDT.asm -o ../obj/Kernel/GDT.o
nasm -f elf32 src/CPUID.asm -o ../obj/Kernel/CPUID.o
gcc -c Kernel.c -o ../obj/Kernel/Kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wpedantic -m32 -I include
gcc -T linker.ld -o ../LilakOSKernelImage.LEF -ffreestanding -O2 -nostdlib -m32 -z max-page-size=0x1000 ../obj/Kernel/boot.o ../obj/Kernel/GDT.o ../obj/Kernel/CPUID.o ../obj/Kernel/Kernel.o
cd ../
#decompile
objdump -D -m i386 LilakOSKernelImage.LEF > kernel.dis
#disk image making
dd if=obj/boot/boot.bin of=LilakOS.img bs=512 seek=0 count=1 conv=notrunc
dd if=obj/boot/stage2.bin of=LilakOS.img bs=512 seek=1 count=2 conv=notrunc
dd if=obj/index/staticindex.sta of=LilakOS.img bs=512 seek=4194303 count=1 conv=notrunc
dd if=LilakOSKernelImage.LEF of=LilakOS.img bs=512 seek=4 conv=notrunc
