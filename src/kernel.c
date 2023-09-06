#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"

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



void kernel_main(){
    init_terminal();
    print("Hello, World!\n");
    idt_init();
    enable_interrupts();
}