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
    idt_entry_encode(to, (uint32_t)from->base, _SEG_OFFSET(from->segment_selector), _TYPE_ATTR(from->type, from->attr));
}

void mafn_kernel_idt_add_entry(uint16_t index, struct easy_IDT_entry new_entry)
{
    if (index < MAFN_KERNEL_IDT_GATES) {
        idt_generate_entry(&new_entry, &mafn_kernel_idt.base[index]);
    }
}

// This is a helper macro for adding an exception since they're all so alike
#define _ADD_EXCEPTION(EXC_NUMBER) mafn_kernel_idt_add_entry( \
    EXC_NUMBER, \
    (struct easy_IDT_entry) { \
        .base = exception ## EXC_NUMBER, \
        .segment_selector = MAFN_KERNEL_CODE_SEGMENT, \
        .type = GATE_32_INT, .attr = ATTR_KERNEL \
    } \
)

void mafn_kernel_idt_init()
{
    memset(&mafn_kernel_idt, 0, sizeof(mafn_kernel_idt));

    _ADD_EXCEPTION(0);
    _ADD_EXCEPTION(1);
    _ADD_EXCEPTION(2);
    _ADD_EXCEPTION(3);
    _ADD_EXCEPTION(4);
    _ADD_EXCEPTION(5);
    _ADD_EXCEPTION(6);
    _ADD_EXCEPTION(7);
    _ADD_EXCEPTION(9);
    _ADD_EXCEPTION(16);
    _ADD_EXCEPTION(18);
    _ADD_EXCEPTION(20);

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
