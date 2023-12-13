#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include "memory/kheap.h"

uint16_t *video_mem = (uint16_t *)(0xB8000);
int row = 0;
int col = 0;

size_t strlen(const char *str){
    size_t len = 0;
    while(str[len]) len++;
    return len;
}

uint16_t encode_char(char c, char color){
    return (color << 8) | c; 
}

void init_terminal(){
    for(int i = 0; i < VGA_HEIGHT; i++){
        for(int j = 0; j < VGA_WIDTH; j++){
            video_mem[i*VGA_WIDTH + j] = encode_char(' ', 0);
        }
    }
}

void put_char(int x, int y, char c, char color){
    video_mem[x*VGA_WIDTH + y] = encode_char(c, color);
}

void print_char(char c, char color){
    if(c == '\n'){
        row++;
        col = 0;
        return;
    }
    put_char(row, col, c, color);
    col++;
    if(col == VGA_WIDTH){
        col = 0;
        row++;
    }
}

void print(const char* str){
    for(size_t i = 0; i < strlen(str); i++){
        print_char(str[i], 15);
    }
}


void print_numbers(uint32_t num){
    int digits[10] = {0};
    int pos = 10;
    while(pos--){
        digits[pos] = num%10;
        num /= 10;
    }
    for(int i = 0; i < 10; i++){
        print_char(digits[i] + '0', 15);
    }
    print_char('\n', 15);
}

void kernel_main(){
    init_terminal();
    print("Hello, World!\n");
    idt_init();
    enable_interrupts();
    kernel_heap_init();
    print_numbers((uint32_t)sizeof(MemChunk));
    void* head = getHead();
    void* ptr1 = kmalloc(5);
    void* ptr2 = kmalloc(6);
    print_numbers((uint32_t)head);
    print_numbers((uint32_t)ptr1);
    print_numbers((uint32_t)ptr2);
    print("\n");
    kfree(ptr1);
    void* ptr3 = kmalloc(4);
    print_numbers((uint32_t)ptr3);
    // print_numbers(69);
}