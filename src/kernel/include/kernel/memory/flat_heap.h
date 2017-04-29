//
// Created by mafn on 4/24/17.
//

#ifndef MAFN_KERNEL_FLAT_HEAP_H
#define MAFN_KERNEL_FLAT_HEAP_H

#include <stdint.h>
#include <stdbool.h>

// Defined / allocated in boot.s
extern void* heap_bottom;
extern void* heap_size;

struct k_flat_memblock
{
    uint32_t size;                      // actual size of memory block (this INCLUDES this struct's size!)
    bool used;

    void* data;

    struct k_flat_memblock* next;
    struct k_flat_memblock* prev;
};

typedef struct k_flat_memblock k_flat_memblock_t;

extern void init_k_flat_heap();

extern void* k_flat_malloc(uint32_t size);
extern void k_flat_free(void* addr);


#endif //MAFN_KERNEL_FLAT_HEAP_H
