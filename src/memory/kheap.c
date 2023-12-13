#include "kheap.h"
#include "../config.h"

MemChunk* kernel_head = 0;

MemChunk* getHead(){return kernel_head;};

void kernel_heap_init(){

    heap_init(&kernel_head, (void*)KERNEL_HEAP_START, (uint32_t)KERNEL_HEAP_SIZE);
}

void* kmalloc(uint32_t size){
    return heap_malloc(kernel_head, size);
}

int kfree(void* ptr){
    return heap_free(kernel_head, ptr);
}