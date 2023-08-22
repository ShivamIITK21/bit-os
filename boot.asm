org 0
BITS 16

jmp 0x7c0:start

start:
    ;segment setup
    cli
    mov ax, 0x7c0
    mov ds, ax
    mov es, ax
    mov ax, 0x7c00
    mov ss, ax
    mov sp, 0x7c00
    sti

    ;loading hard disk
    mov ah, 2   ;read sector
    mov al, 1   ;read one sector
    mov ch, 0   ;low 8 bits
    mov cl, 2   ;segment num
    mov dh, 0   ;head
    mov bx, buffer
    int 0x13

    jc error

    mov si, buffer
    call print
    jmp $


error:
    mov si, error_msg
    call print
    jmp $

print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    mov ah, 0eh
    int 0x10
    jmp .loop
.done:
    ret

error_msg: db 'Failed to load sector', 0

times 510-($ - $$) db 0
dw 0xAA55

buffer:
