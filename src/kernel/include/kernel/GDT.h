//
// Created by mafn on 3/5/17.
//

#ifndef MAFN_KERNEL_GDT_H
#define MAFN_KERNEL_GDT_H

#include <stdint.h>

/* GDT resources:
 * - "wiki.osdev.org/GDT"
 * - Volume 3, Chapter 3.4.5 of the Intel IA32 reference manual
 */

/* mafn's GDT Entry explanation:
 *
 * Segment = chunk of memory with certain CPU properties
 *
 * Limit              (20 bits) = Maximum adressable unit (linear address or page depending on Granularity bit)
 * Base               (32 bits) = Base adress of segment
 * Access / type byte (8 bits)  = Bunch of bits which decide what gets to access this segment
 * Flags              (4 bits)  = Special flags (granularity & size bit)
 *
 */

/* Access / type byte [byte 5 (bit 40-47)]:
 *
 * 0 Ac = Accessed bit, used by the CPU. Set to 0.
 * 1 RW = Read/Write bit.
 *        For EX=0 (Data segment), this is a Writable flag.
 *        For EX=1 (Code segment), this is a Readable flag.
 * 2 DC = Direction/Conforming bit.
 *        For EX=0 (Data segment), this decides which direction this segment grows in
 *          DC=0, segment grows up
 *          DC=1, segment grows down
 *        For EX=1 (Code segment), this decides whether lower privilege levels than Privl get to execute stuff in this segment
 * 3 EX = Executable bit.
 *        EX=0, segment is a data segment
 *        EX=1, segment is a code segment
 * 4 S  = Specifies whether this is a system segment or Code/Data segment
 *        S=1, Code/Data segment
 * 5-6 Privl = Privilege level
 *             Privl=0, kernel privilege level
 *             Privl=3, user privilege level
 * 7 Pr = Present bit, should be 1 for custom segments
 */

/* Granularity byte [byte 6](bit 48-55):
 * 0-3 Limit upper 4 bits
 * 4 X
 * 5 X
 * 6 Sz = Size bit
 *        Sz=0, 16 bit protected mode
 *        Sz=1, 32 bit protected mode
 * 7 Gr = Granularity bit
 *        Gr=0, limit is in 1B blocks
 *        Gr=1, limit is in 4KiB blocks (paging)
 */

// Access / type byte macros
#define TYPE_AC(bit) (bit << 0)
#define TYPE_RW(bit) (bit << 1)
#define TYPE_DC(bit) (bit << 2)
#define TYPE_EX(bit) (bit << 3)
#define TYPE_S(bit) (bit << 4)
#define TYPE_PRIV(bit) (bit << 5)
#define TYPE_PR(bit) (bit << 7)

#define TYPE_CODE TYPE_AC(0) | TYPE_RW(1) | TYPE_DC(0) | TYPE_EX(1) | TYPE_S(1) | TYPE_PRIV(0) | TYPE_PR(1)
#define TYPE_DATA TYPE_AC(0) | TYPE_RW(1) | TYPE_DC(0) | TYPE_EX(0) | TYPE_S(1) | TYPE_PRIV(0) | TYPE_PR(1)

// Granularity byte macros
#define GRAN_SZ(bit) (bit << 6)
#define GRAN_GR(bit) (bit << 7)
#define GRAN_BYTE (GRAN_SZ(1) | GRAN_GR(0))
#define GRAN_PAGE (GRAN_SZ(1) | GRAN_GR(1))

// This corresponds to 4KiB
#define FROM_BYTES_TO_PAGES(limit) (limit >> 12)

// This needs to be packed so GCC doesn't fuck with internal alignment of bytes
struct GDT_entry {
    uint16_t limit_L;
    uint16_t base_L;
    uint8_t  base_HL;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_HH;
} __attribute__((packed));

// This needs to be packed so GCC doesn't fuck with internal alignment of bytes
struct GDT {
    uint16_t limit;
    struct GDT_entry* base_addr;
} __attribute__((packed));

struct easy_GDT_entry {
    uint16_t base;
    uint32_t limit;
    uint8_t type;
    uint8_t granularity;
};

#define MAFN_KERNEL_SEGMENTS 16
#define MAFN_KERNEL_CODE_SEGMENT 1
#define MAFN_KERNEL_DATA_SEGMENT 2
// This comes down to multiplying the segment with sizeof(GDT_entry)
#define _SEG_OFFSET(seg) (uint16_t)(seg << 3)

extern struct GDT_entry mafn_kernel_gdt_entries[MAFN_KERNEL_SEGMENTS];
extern struct GDT       mafn_kernel_gdt;

extern void gdt_entry_encode(struct GDT_entry* entry, uint8_t granularity, uint8_t type, uint32_t limit, uint32_t base);
extern void gdt_generate_entry(struct easy_GDT_entry* from, struct GDT_entry* to);
extern void gdt_flush(struct GDT* new_gdt);

extern void mafn_kernel_gdt_init();
extern void mafn_kernel_gdt_add_entry(uint16_t index, struct easy_GDT_entry new_entry);

#endif //MAFN_KERNEL_GDT_H
