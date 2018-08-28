section .bss
align 0x10
stackbottom:
resb 0x4000
stacktop:

section .text
global _start:function (_start.end - _start)
_start:
    pop eax
    mov esp, 0x90000
    push eax
    extern CKernelFunction
    call CKernelFunction
    jmp $
.end:
    hlt
    jmp .end
