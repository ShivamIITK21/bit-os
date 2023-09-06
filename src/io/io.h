#ifndef IO_H
#define IO_H
#include<stdint.h>

extern unsigned char insb(uint16_t port);
extern uint16_t insw(uint16_t port);
extern void outb(uint16_t port, unsigned char val);
extern void outw(uint16_t port, uint16_t val);

#endif