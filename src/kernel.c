#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include "memory/kheap.h"
#include "io/mouse.h"
#include "idt/pic.h"

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

//can print upto 10 digits
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

void print_numbers_using_heap(uint32_t num){
    if(num == 0){
        print("0\n");
        return;
    }

    uint32_t cpy = num;
    uint32_t len = 0;
    while(cpy != 0) {
        len++;
        cpy /= 10;
    }
    uint32_t *arr = (uint32_t*)kmalloc(len*sizeof(uint32_t));
    int pos = len;
    while(pos--){
        arr[pos] = num%10;
        num /= 10;
    }
    for(int i = 0; i < len; i++){
        print_char(arr[i] + '0', 15);
    }
    print_char('\n', 15);
    // kfree(arr);
}

void kernel_main(){
    init_terminal();
    print("Hello, World!\n");
    InitialiseMouse();
    idt_init();
    enable_interrupts();
    kernel_heap_init();
    print("Back to kernel\n");
}