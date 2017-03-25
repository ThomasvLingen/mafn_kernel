//
// Created by mafn on 3/11/17.
//

#ifndef MAFN_KERNEL_IDT_H
#define MAFN_KERNEL_IDT_H

#include <stdint.h>

/* mafn's IDT entry explanation:
 *
 * An IDT entry describes where the handler for an interrupt is located.
 * - This includes exceptions      [index 0-31  ]
 * - This includes custom handlers [index 32-...]
 *
 * Offset     (16 bits) = address of the handler (more correctly, ISR entry point)
 * Selector   (16 bits) = selector of the segment that the interrupt runs in (usually kernel code segment)
 * Type       (4 bits)  = interrupt type, see below
 * Attributes (4 bits)  = interrupt attributes (Present / Storage / Privelege level)
 */

/* Type nibble (type_attr bit 0-3)
 *
 * 0x5 = 32-bit Task Gate
 * 0xE = 32-bit Interrupt Gate
 * 0xF = 32-bit Trap Gate
 * 0x6 = 16-bit Interrupt Gate
 * 0x7 = 16-bit Trap Gate
 *
 * Interrupt Gate
 * - Can be called with the `int` instruction (e.g `int 0x80`)
 * - Returns with the `iret` instruction
 *
 * Trap Gate
 * [XXX: Document this]
 *
 * Task Gate
 * [XXX: Document this]
 */

/* Attributes nibble (type_attr bit 4-7)
 * 4   S   = Storage bit ??? Seems to always be 0 for me
 * 5-6 DPL = Descriptor privilege level, Specifies minimum run level for the interrupt to be called from (usually 0)
 * 7   P   = Present bit, 1 for used interrupts
 */

/* Protected mode exceptions [index 0-31]
 *
 * See IA32.pdf Vol 3. Chapter 6.3.1
 */

// Gate type macros
#define GATE_32_TASK 0x5
#define GATE_32_INT 0xE
#define GATE_32_TRAP 0xF
#define GATE_16_INT 0x6
#define GATE_16_TRAP 0x7

// Attribute macros
#define ATTR_S(bit) (bit << 0)
#define ATTR_DPL(bit) (bit << 1)
#define ATTR_P(bit) (bit << 3)
#define ATTR_KERNEL ATTR_S(0) | ATTR_DPL(0) | ATTR_P(1)

#define _TYPE_ATTR(type, attr) (uint8_t)((attr << 4) | (type & 0x0F))

// This needs to be packed so GCC doesn't fuck with internal alignment of bytes
struct IDT_entry {
    uint16_t offset_L;
    uint16_t segment_selector;
    uint8_t  zero;
    uint8_t type_attr;
    uint16_t offset_H;
} __attribute__((packed));

// This needs to be packed so GCC doesn't fuck with internal alignment of bytes
struct IDT {
    uint16_t limit;
    struct IDT_entry* base;
} __attribute__((packed));

struct easy_IDT_entry {
    void* base;
    uint16_t segment_selector;
    uint8_t type;
    uint8_t attr;
};

extern void idt_entry_encode(struct IDT_entry* entry, uint32_t base, uint16_t segment_selector, uint8_t type_attr);
extern void idt_generate_entry(struct easy_IDT_entry* from, struct IDT_entry* to);
extern void idt_install(struct IDT* new_idt);

#endif //MAFN_KERNEL_IDT_H
