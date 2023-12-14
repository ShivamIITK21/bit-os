#ifndef KEYBOARD_H
#define KEYBOARD_H
#include<stdint.h>
#include "io.h"
#include "../kernel.h"

#define KEYBOARD_DATA_PORT     0x60
#define KEYBOARD_COMMAND_PORT  0x64

uint8_t read_scan_code();
void scan_code_to_action(uint8_t key);
void keyboard_init();

#endif