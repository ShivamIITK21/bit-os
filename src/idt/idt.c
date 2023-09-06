#include "idt.h"
#include "../config.h"
#include "../memory/memory.h"
#include "../kernel.h"
#include "../io/io.h"


extern void int0();
extern void int21h();
extern void load_idt(void *ptr);

struct idt_desc idt_descriptors[MAX_INTERRUPTS];
struct idtr_desc idtr_descriptor;

void no_interrupt_handler(){
    outb(0x20, 0x20);
}

void int21h_handler(){
    print("Key Pressed\n");
    outb(0x20, 0x20);
}

void int0_handler(){
    print("Divide by Zero Error!\n");
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

    load_idt(&idtr_descriptor);

}

