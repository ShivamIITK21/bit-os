#include "kernel.h"

uint16_t *video_mem = (uint16_t *)(0xB8000);

uint16_t encode_char(char c, char col){
    return (col << 8) | c; 
}

void init_terminal(){
    for(int i = 0; i < VGA_HEIGHT; i++){
        for(int j = 0; j < VGA_WIDTH; j++){
            video_mem[i*VGA_WIDTH + j] = encode_char(' ', 0);
        }
    }
}

void print_string(char *string, int len){
    for(int i = 0; i < len; i++){
        video_mem[i] = encode_char(string[i], 15);
    }
}

void kernel_main(){
    init_terminal();
    char *string = "Hello, World!";
    print_string(string, 13);
}