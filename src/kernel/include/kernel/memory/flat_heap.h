//
// Created by mafn on 4/24/17.
//

#ifndef MAFN_KERNEL_FLAT_HEAP_H
#define MAFN_KERNEL_FLAT_HEAP_H

#include <kernel/numerics.h>
#include <stdbool.h>

#define K_FLAT_HEAP_SIZE MiB_SIZE

struct k_flat_memblock
{
    uint32_t size;                      // actual size of memory block (this INCLUDES this struct's size!)
    bool used;

    void* data;

    struct k_flat_memblock* next;
    struct k_flat_memblock* prev;
};

typedef struct k_flat_memblock k_flat_memblock_t;

extern uint8_t k_flat_heap[K_FLAT_HEAP_SIZE];
extern uint8_t* k_flat_heap_start;
extern uint8_t* k_flat_heap_end;

extern void init_k_flat_heap();

extern void* k_flat_malloc(uint32_t size);
extern void k_flat_free(void* addr);


#endif //MAFN_KERNEL_FLAT_HEAP_H
