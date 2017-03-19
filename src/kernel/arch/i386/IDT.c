//
// Created by mafn on 3/11/17.
//
#include <kernel/IDT.h>

#include <kernel/print.h>
#include <kernel/numerics.h>
#include <kernel/GDT.h>

#include <string.h>
#include <stdbool.h>
#include <kernel/vgaterm.h>
#include "vga.h"

struct IDT_entry mafn_kernel_idt_entries[MAFN_KERNEL_IDT_GATES];
struct IDT       mafn_kernel_idt = {
    .limit = sizeof(mafn_kernel_idt_entries) - 1,
    .base = mafn_kernel_idt_entries
};

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
    // H = attr_L; L = type_L
    uint8_t type_attr = ((from->attr & 0x0F) << 4) | (from->type & 0x0F);

    idt_entry_encode(to, from->base, from->segment_selector, type_attr);
}

void mafn_kernel_idt_add_entry(uint16_t index, uint32_t base, uint16_t selector, uint8_t type, uint8_t attr)
{
    if (index < MAFN_KERNEL_IDT_GATES) {
        idt_entry_encode(&mafn_kernel_idt.base[index], base, selector, _TYPE_ATTR(type, attr));
    }
}

void mafn_kernel_idt_init()
{
    memset(&mafn_kernel_idt, 0, sizeof(mafn_kernel_idt));

    ADD_EXCEPTION(0);
    ADD_EXCEPTION(1);
    ADD_EXCEPTION(2);
    ADD_EXCEPTION(3);
    ADD_EXCEPTION(4);
    ADD_EXCEPTION(5);
    ADD_EXCEPTION(6);
    ADD_EXCEPTION(7);
    ADD_EXCEPTION(9);
    ADD_EXCEPTION(16);
    ADD_EXCEPTION(18);
    ADD_EXCEPTION(20);

    idt_install(&mafn_kernel_idt);
}

bool _is_exception(uint32_t interrupt_number)
{
    return interrupt_number < 20;
}

void _mafn_kernel_fault_handler(struct isr_regs cpu_state)
{
    if (_is_exception(cpu_state.interrupt_i)) {
        vgaterm_setcolour(get_vga_colour_entry(VGA_BLACK, VGA_RED));

        k_puts("FUCK, CPU EXCEPTION\n");

        // TODO: Write proper generic handler
        if (cpu_state.interrupt_i == 0) {
            k_puts("DIVIDE BY 0\n");
        }
        else if (cpu_state.interrupt_i == 3) {
            k_puts("BREAKPOINT\n");
        }

        while (true) {
            asm("nop");
        }
    }
}
