org 0x7c00
BITS 16

CODE_SEG equ gdt_code-gdt_start
DATA_SEG equ gdt_data-gdt_start

jmp 0:start

start:
    ;segment setup
    cli
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    sti


load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax    
    jmp CODE_SEG:load_32

;GDT Table
gdt_start:

gdt_null:
    dd 0x0
    dd 0x0

gdt_code:   ;CS points to this
    dw 0xffff
    dw 0
    db 0
    db 0x9a 
    db 11001111b
    db 0

gdt_data:   ;DS, SS, ES, FS, GS point here
    dw 0xffff
    dw 0
    db 0
    db 0x92 
    db 11001111b
    db 0

gdt_end:

gdt_descriptor:
    dw gdt_end-gdt_start-1
    dd gdt_start


[BITS 32]
load_32:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp
    
    jmp $

times 510-($ - $$) db 0
dw 0xAA55 ;little endian, 0x55AA is the boot signature
