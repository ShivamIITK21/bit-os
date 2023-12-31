section .asm
extern int21h_handler
extern no_interrupt_handler
extern int0_handler
extern int20h_handler
extern int2Ch_handler

global load_idt
global int21h   
global no_interrupt
global int0
global int20h
global int2Ch
global enable_interrupts
global disable_interrupts

enable_interrupts:
    sti
    ret

disable_interrupts:
    cli
    ret

load_idt:
    push ebp
    mov ebp, esp

    mov ebx, [ebp + 8]
    lidt [ebx]

    pop ebp
    ret



no_interrupt:
    cli
    pushad
    call no_interrupt_handler
    popad
    sti
    iret

int0:
    cli
    pushad
    call int0_handler
    popad
    sti
    iret

int20h:
    cli
    pushad
    call int20h_handler
    popad
    sti
    iret

int21h:
    cli
    pushad
    call int21h_handler
    popad
    sti
    iret

int2Ch:
    cli
    pushad
    call int2Ch_handler
    popad
    sti
    iret