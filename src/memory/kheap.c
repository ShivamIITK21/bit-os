#include<kheap.h>
#include<../config.h>

void kernel_heap_init(){

    heap_init(head, (void*)KERNEL_HEAP_START, (uint32_t)KERNEL_HEAP_SIZE);
}

void* kmalloc(uint32_t size){
    return heap_malloc(head, size);
}

int kfree(void* ptr){
    return heap_free(head, ptr);
}