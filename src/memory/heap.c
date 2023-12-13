#include "heap.h"

void heap_init(MemChunk** head, void* start, uint32_t size){
    *head = (MemChunk*)start;
    (*head)->alloc = 0;
    (*head)->next = 0;
    (*head)->prev = 0;
    (*head)->size = size - (uint32_t)sizeof(MemChunk);
}

void* heap_malloc(MemChunk* head, uint32_t size){
    MemChunk* free_chunk = 0;
    for(MemChunk* chunk = head; chunk != 0; chunk = chunk->next){
        if(chunk->size > size && chunk->alloc == 0){
            free_chunk = chunk;
            break;
        }
    }

    if(free_chunk == 0) return 0;

    if(free_chunk->size <= size + (uint32_t)sizeof(MemChunk)){
        free_chunk->alloc = 1;
    }
    else{
        MemChunk* leftover = (MemChunk*)((uint32_t)free_chunk + size + (uint32_t)sizeof(MemChunk));
        leftover->alloc = 0;
        leftover->size = free_chunk->size - size - (uint32_t)sizeof(MemChunk);
        leftover->next = free_chunk->next;
        leftover->prev = free_chunk;

        if(leftover->next != 0) leftover->next->prev = leftover;

        free_chunk->alloc = 1;
        free_chunk->size = size;
        free_chunk->next = leftover;
    }

    return (void*)((uint32_t)free_chunk + sizeof(MemChunk));
}

int heap_free(MemChunk* head, void* ptr){
    MemChunk* chunk = (MemChunk*)((uint32_t)ptr - (uint32_t)sizeof(MemChunk));
    chunk->alloc = 0;

    if(chunk->prev != 0 && chunk->prev->alloc == 0){
        MemChunk* prev_chunk = chunk->prev;
        prev_chunk->size = prev_chunk->size + chunk->size + (uint32_t)sizeof(MemChunk);
        prev_chunk->next = chunk->next;

        if(prev_chunk->next != 0) prev_chunk->next->prev = prev_chunk;
        chunk = prev_chunk;
    }

    if(chunk->next != 0 && chunk->next->alloc == 0){
        MemChunk* next_chunk = chunk->next;
        chunk->size = chunk->size + next_chunk->size + (uint32_t)sizeof(MemChunk);
        chunk->next = next_chunk->next;
        if(next_chunk->next != 0) next_chunk->next->prev = chunk;
    }

    return 0;
}