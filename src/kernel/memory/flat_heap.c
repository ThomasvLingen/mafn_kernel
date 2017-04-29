//
// Created by mafn on 4/24/17.
//

#include <kernel/memory/flat_heap.h>
#include <kernel/print.h>
#include <stddef.h>

static k_flat_memblock_t* _get_root();
static bool _can_use(k_flat_memblock_t* blk, uint32_t size);
static bool _is_perfect_fit(k_flat_memblock_t* blk, uint32_t size);
static void* _split_blk(k_flat_memblock_t* original, uint32_t new_blk_size);
static void* _use_blk(k_flat_memblock_t* to_use);
static void* _get_block_data(k_flat_memblock_t* block);

void init_k_flat_heap()
{
    k_flat_memblock_t* root = _get_root();

    root->size = (uint32_t)&heap_size;
    root->used = false;

    root->data = _get_block_data(root);

    root->prev = NULL;
    root->next = NULL;
}

void* k_flat_malloc(uint32_t size)
{
    // We need to make room for the block struct as well
    uint32_t total_size = size + sizeof(k_flat_memblock_t);

    for (k_flat_memblock_t* current_blk = _get_root();
         current_blk != NULL;
         current_blk = current_blk->next)
    {
        // Case 1: block fits perfectly!
        if (_is_perfect_fit(current_blk, total_size)) {
            return _use_blk(current_blk);
        }

        // Case 2: block has enough space, but space is too much so it has to be split
        if (_can_use(current_blk, total_size)) {
            return _split_blk(current_blk, total_size);
        }
    }

    k_puts("flat_heap: no useable blocks...\n");
    return NULL;
}

extern void k_flat_free(void* addr)
{
    // null ptr safety
    if (addr == NULL) {
        return;
    }

    k_flat_memblock_t* block = (k_flat_memblock_t*) addr - sizeof(k_flat_memblock_t);
}

// size means total_size of the new block
static bool _can_use(k_flat_memblock_t* blk, uint32_t size)
{
    bool is_free          = !blk->used;
    bool has_enough_space = (blk->size >= size + sizeof(k_flat_memblock_t));

    return is_free && has_enough_space;
}

// size means total_size of the new block
static bool _is_perfect_fit(k_flat_memblock_t* blk, uint32_t size)
{
    bool is_free = !blk->used;
    return is_free && blk->size == size;
}

static void* _split_blk(k_flat_memblock_t* original, uint32_t new_blk_size)
{
    // Sanity check
    if (original->size <= sizeof(k_flat_memblock_t) + new_blk_size) {
        k_puts("flat_heap: impossible split...\n");

        while (true) {
            asm("nop");
        }

        return NULL;
    }

    k_flat_memblock_t* original_next = original->next;

    // Make the new remainder block
    k_flat_memblock_t* remainder_block = (k_flat_memblock_t*)((uint32_t)original + new_blk_size);
    remainder_block->size = original->size - new_blk_size;
    remainder_block->used = false;
    remainder_block->data = _get_block_data(remainder_block);
    remainder_block->prev = original;
    remainder_block->next = original_next;

    // Use the old block
    original->size = new_blk_size;
    original->used = true;
    original->data = _get_block_data(original);
    original->next = remainder_block;

    return original->data;
}

static void* _use_blk(k_flat_memblock_t* to_use)
{
    to_use->used = true;

    return to_use->data;
}

static void* _get_block_data(k_flat_memblock_t* block)
{
    return block + 1;
}

static k_flat_memblock_t* _get_root()
{
    return (k_flat_memblock_t*) &heap_bottom;
}