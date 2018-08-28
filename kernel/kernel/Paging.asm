section .text

global SetPageRegister
SetPageRegister:
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    
    xor eax, eax

    mov eax, [esp+4]
    mov cr3, eax


    ret
