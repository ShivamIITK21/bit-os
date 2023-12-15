#include "mouse.h"

#include "mouse.h"

void InitialiseMouse() {
    // Enable auxiliary mouse device
    outb(MOUSE_COMMAND_PORT, 0xA8);

    // Enable the interrupts
    outb(MOUSE_COMMAND_PORT, 0x20); // command 0x20 - get controller status
    uint8_t status = insb(MOUSE_DATA_PORT) | 2;
    outb(MOUSE_COMMAND_PORT, 0x60); // command 0x60 - set controller status
    outb(MOUSE_DATA_PORT, status);

    // Tell the mouse to use default settings
    outb(MOUSE_COMMAND_PORT, 0xD4);
    outb(MOUSE_DATA_PORT, 0xF6);
    insb(MOUSE_DATA_PORT);  // Acknowledge

    // Enable the mouse
    outb(MOUSE_COMMAND_PORT, 0xD4);
    outb(MOUSE_DATA_PORT, 0xF4);
    insb(MOUSE_DATA_PORT);  // Acknowledge
}

void MouseWrite(unsigned char data) {
    outb(0x64, 0xd4);
    outb(0x60, data);
}

unsigned char MouseRead() {
    return insb(0x60);
}
