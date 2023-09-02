#ifndef KERNEL_H
#define KERNEL_H
#include<stdint.h>
#include<stddef.h>
#define VGA_HEIGHT 20
#define VGA_WIDTH 80

uint16_t encode_char(char c, char col);
size_t strlen(const char* str);
void init_terminal();
void print_string(char *string);
void kernel_main();

#endif