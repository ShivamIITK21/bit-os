#include "mouse.h"

void InitialiseMouse() {
    outb(MOUSE_COMMAND_PORT, 0xA8);
    outb(MOUSE_COMMAND_PORT, 0x20);
    uint8_t status = insb(MOUSE_DATA_PORT) | 2;
    outb(MOUSE_COMMAND_PORT, 0x60);
    outb(MOUSE_DATA_PORT, status);
    outb(MOUSE_COMMAND_PORT, 0xD4);
    outb(MOUSE_DATA_PORT, 0xF4);
    insw(MOUSE_DATA_PORT);
}

void MouseWrite(unsigned char data) {
    outb(0x64, 0xd4);
    outb(0x60, data);
}

unsigned char MouseRead() {
    return insb(0x60);
}
