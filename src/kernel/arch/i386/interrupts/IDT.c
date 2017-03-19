//
// Created by mafn on 3/11/17.
//
#include <kernel/interrupts/IDT.h>

#include <kernel/numerics.h>
#include <kernel/GDT.h>


void idt_entry_encode(struct IDT_entry* entry, uint32_t base, uint16_t segment_selector, uint8_t type_attr)
{
    // Encode base (offset)
    entry->offset_L = U32_LOW(base);
    entry->offset_H = U32_HIGH(base);

    // Encode segment selector
    entry->segment_selector = segment_selector;

    // Encode type / attr
    entry->type_attr = type_attr;

    // Encode 0
    entry->zero = 0;
}

void idt_generate_entry(struct easy_IDT_entry* from, struct IDT_entry* to)
{
    idt_entry_encode(to, (uint32_t)from->base, _SEG_OFFSET(from->segment_selector), _TYPE_ATTR(from->type, from->attr));
}
