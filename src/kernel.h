#ifndef KERNEL_H
#include<stdint.h>
#define KERNEL_H
#define VGA_HEIGHT 20
#define VGA_WIDTH 80

uint16_t encode_char(char c, char col);
void init_terminal();
void kernel_main();

#endif