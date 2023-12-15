[BITS 32]
global _start
extern kernel_main
extern PIC_remap
CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, stack_end      ;set stack ptr
    mov esp, ebp

    ; Enable the A20 line
    in al, 0x92
    or al, 2
    out 0x92, al
    
    ; Remap the master PIC
    ; mov al, 00010001b
    ; out 0x20, al

    ; mov al, 0x20 
    ; out 0x21, al

    ; mov al, 00000001b
    ; out 0x21, al
pic_remap:
    push 0x28
    push 0x20
    call PIC_remap
    pop eax
    pop eax

    call kernel_main

    jmp $

stack_begin:
    resb 4096   ;reserve stack space

stack_end:

times 5120-($ - $$) db 0
