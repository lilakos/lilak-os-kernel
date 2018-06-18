#C
nasm -felf32 kernel/boot/kernel.asm -o obj/boot.o
gcc -m32 -c kernel/kernel/string.c -I kernel/include -o obj/string.o
gcc -m32 -c kernel/kernel/TTY.c -I kernel/include -o obj/TTY.o
gcc -m32 -c kernel/kernel/stdio.c -I kernel/include -o obj/stdio.o
gcc -m32 -c kernel/kernel/system.c -I kernel/include -o obj/system.o


gcc -m32 -c kernel/kernel/kernel.c -I kernel/include -o obj/kernelc.o
ld -m elf_i386 -T kernel/link.ld -o kernel.bin obj/boot.o obj/string.o obj/TTY.o obj/stdio.o obj/system.o obj/kernelc.o 

#Linking

#Making the disk image
dd if=obj/bootloader/boot.bin of=LilakOS.img bs=512 conv=notrunc
dd if=obj/stage2/stage2.bin of=LilakOS.img bs=512 seek=1 conv=notrunc
dd if=obj/staticindex/index.bin of=LilakOS.img bs=512 conv=notrunc seek=2097151
dd if=kernel.bin of=LilakOS.img bs=512 conv=notrunc seek=3 
#Disassembling
ndisasm obj/bootloader/boot.bin >  disassembled/bootloader/boot.dis
ndisasm obj/stage2/stage2.bin >  disassembled/stage2/stage2.dis

#Decompiling
objdump -D  -m i386 kernel.bin > kernel.dis

#Done!
echo Done!
