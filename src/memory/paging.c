#include "paging.h"
#include "kheap.h"

page_directory_t linear_page_diretory(uint8_t flags){
    page_directory_t page_directory = (page_directory_t)kmalloc(PAGE_DIRECTORY_SIZE*sizeof(uint32_t));
    for(int i = 0; i < PAGE_DIRECTORY_SIZE; i++){
        page_table_t page_table = (page_table_t)kmalloc(PAGE_TABLE_SIZE*sizeof(uint32_t));
        for(int j = 0; j < PAGE_TABLE_SIZE; j++){
            page_table[j] = (i*PAGE_TABLE_SIZE*PAGE_SIZE + (j*PAGE_SIZE)) | flags;
        }
        page_directory[i] = (uint32_t)page_table | flags | WRITEABLE;
    }
    return page_directory;
}