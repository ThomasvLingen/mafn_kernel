//
// Created by mafn on 3/5/17.
//

#include <kernel/GDT.h>
#include <kernel/numerics.h>
#include <string.h>

struct GDT_entry mafn_kernel_gdt_entries[MAFN_KERNEL_SEGMENTS];
struct GDT mafn_kernel_gdt = {
    .limit = sizeof(mafn_kernel_gdt_entries) - 1,
    .base_addr = mafn_kernel_gdt_entries
};

void gdt_entry_encode(struct GDT_entry* entry, uint8_t granularity, uint8_t type, uint32_t limit, uint32_t base)
{
    // Encode base
    entry->base_L  = (uint16_t)(base        & 0x0000FFFF);
    entry->base_HL = (uint8_t)((base >> 16) & 0x000000FF);
    entry->base_HH = (uint8_t)((base >> 24) & 0x000000FF);

    // Encode limit (of which 4 bits reside in the granularity field)
    entry->limit_L     = (uint16_t)(limit        & 0x0000FFFF);
    entry->granularity = (uint8_t) ((limit >> 16) & 0x0000000F);

    // Encode Access
    entry->access = type;

    // Encode Granularity (which resides in the upper 4 bits of the granularity field)
    entry->granularity = entry->granularity | (granularity & 0xF0);
}

void gdt_generate_entry(struct easy_GDT_entry* from, struct GDT_entry* to)
{
    uint32_t limit;

    if (from->granularity == GRAN_PAGE) {
        limit = FROM_BYTES_TO_PAGES(from->limit);
    } else {
        limit = from->limit;
    }

    gdt_entry_encode(to, from->granularity, from->type, limit, from->base);
}

void mafn_kernel_gdt_add_entry(uint16_t index, struct easy_GDT_entry new_entry)
{
    if (index < MAFN_KERNEL_SEGMENTS) {
        gdt_generate_entry(&new_entry, &mafn_kernel_gdt.base_addr[index]);
    }
}

void mafn_kernel_gdt_init()
{
    struct easy_GDT_entry null_descriptor = {
        .base        = 0x0,
        .limit       = 0x0,
        .type        = 0x0,
        .granularity = 0x0
    };

    struct easy_GDT_entry code_segment = {
        .base        = 0x0,
        .limit       = GiB_SIZE-1,
        .type        = TYPE_CODE,
        .granularity = GRAN_PAGE
    };

    struct easy_GDT_entry data_segment = {
        .base        = 0x0,
        .limit       = GiB_SIZE-1,
        .type        = TYPE_DATA,
        .granularity = GRAN_PAGE
    };

    memset(mafn_kernel_gdt_entries, 0, sizeof(mafn_kernel_gdt_entries));

    mafn_kernel_gdt_add_entry(0, null_descriptor);
    mafn_kernel_gdt_add_entry(1, code_segment);
    mafn_kernel_gdt_add_entry(2, data_segment);

    gdt_flush(&mafn_kernel_gdt);
}
