section .text

extern TTYWriteString

global CPUInfo
CPUInfo:
    xor eax, eax
    
    cpuid

    mov [cpuname], ebx
    mov [nameedx], edx
    mov [nameecx], ecx


    mov eax, cpuname
    push eax

    call TTYWriteString
    jmp .exit
.exit:
    ret


cpuname: dd 0x00000000
nameedx dd 0x00000000
nameecx dd 0x00000000
db 0x00