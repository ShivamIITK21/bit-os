#ifndef MOUSE_H
#define MOUSE_H

#define MOUSE_DATA_PORT     0x60
#define MOUSE_COMMAND_PORT  0x64

#include "io.h"

void InitialiseMouse();
void MouseWrite(unsigned char data);
unsigned char MouseRead();

#endif