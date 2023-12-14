#include "idt.h"
#include "../config.h"
#include "../memory/memory.h"
#include "../kernel.h"
#include "../io/io.h"
#include "../io/keyboard.h"
#include "../io/mouse.h"

extern void int0();
extern void int20h();
extern void int21h();
extern void int2Ch();
extern void load_idt(void *ptr);

struct idt_desc idt_descriptors[MAX_INTERRUPTS];
struct idtr_desc idtr_descriptor;

void no_interrupt_handler(){
    outb(0x20, 0x20);
}

void int0_handler(){
    print("Divide by Zero Error!\n");
    outb(0x20, 0x20);
}

void int20h_handler(){
    print("tick\n");
    outb(0x20, 0x20);
}

void int21h_handler(){
    print("????");
    unsigned char c = read_scan_code();
    scan_code_to_action(c);
    outb(0x20, 0x20);
}

void int2Ch_handler(){
    print("mouse moved\n");
    // insb(MOUSE_COMMAND_PORT);
    // insb(MOUSE_DATA_PORT);
    outb(0x20, 0x20);
}

void idt_set(int interrupt_no, void* address)
{
    struct idt_desc* desc = &idt_descriptors[interrupt_no];
    desc->offset_1 = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x00;
    desc->type_attributes = 0xEE;
    desc->offset_2 = (uint32_t) address >> 16;
}


void idt_init(){
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptor.limit = sizeof(idt_descriptors)-1;
    idtr_descriptor.base = (uint32_t)idt_descriptors;

    for(int i = 0; i < MAX_INTERRUPTS; i++) idt_set(i, no_interrupt);

    idt_set(0, int0);
    idt_set(0x21, int21h);
    idt_set(0x2C, int2Ch);
    // idt_set(0x20, int20h);

    load_idt(&idtr_descriptor);

}

