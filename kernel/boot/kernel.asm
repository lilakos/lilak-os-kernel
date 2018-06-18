section .bss
align 16
stack_bottom:
resb 32768
stack_top:
 
section .text
global _start:function (_start.end - _start)
_start:
	cli
	mov esp, stack_top

	extern kernel_main
	call kernel_main

	cli
.hang:	hlt
	jmp .hang
.end: