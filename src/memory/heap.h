#ifndef HEAP_H
#define HEAP_H
#include<stdint.h>


typedef struct MemChunk{
    uint32_t size;
    struct MemChunk* prev;
    struct MemChunk* next;
    uint8_t alloc;
}MemChunk;

void heap_init(MemChunk** head, void* start, uint32_t size);
void* heap_malloc(MemChunk* head, uint32_t size);
int heap_free(MemChunk* head, void* ptr);

#endif