#ifndef KHEAP_H
#define KHEAP_H
#include<heap.h>

MemChunk* head;


void kernel_heap_init();
void* kmalloc(uint32_t size);
int kfree(void* ptr);


#endif