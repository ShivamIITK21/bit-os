#ifndef PAGING_H
#define PAGING_H
#include <stdint.h>

#define PAGE_SIZE 4096
#define PAGE_TABLE_SIZE 1024
#define PAGE_DIRECTORY_SIZE 1024
#define CACHE_DISABLED   0b00010000
#define WRITE_THROUGH    0b00001000
#define ACCESS_FROM_ALL  0b00000100
#define WRITEABLE        0b00000010
#define PRESENT          0b00000001 


typedef uint32_t* page_directory_t;
typedef uint32_t* page_table_t;

page_directory_t linear_page_diretory(uint8_t flags);

#endif 
