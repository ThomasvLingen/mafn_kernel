//
// Created by mafn on 3/19/17.
//

#ifndef MAFN_KERNEL_INTERRUPT_H
#define MAFN_KERNEL_INTERRUPT_H

#include <stdint.h>

#include <kernel/interrupts/IDT.h>

#define MAFN_KERNEL_IDT_GATES 256

extern struct IDT_entry mafn_kernel_idt_entries[MAFN_KERNEL_IDT_GATES];
extern struct IDT       mafn_kernel_idt;

extern void mafn_kernel_idt_add_entry(uint16_t index, struct easy_IDT_entry new_entry);
extern void mafn_kernel_idt_init();

// Exceptions
struct isr_regs {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt_i, error_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

extern void _mafn_kernel_fault_handler(struct isr_regs cpu_state);

extern void exception0(void);
extern void exception1(void);
extern void exception2(void);
extern void exception3(void);
extern void exception4(void);
extern void exception5(void);
extern void exception6(void);
extern void exception7(void);
extern void exception9(void);
extern void exception16(void);
extern void exception18(void);
extern void exception19(void);
extern void exception20(void);

#endif //MAFN_KERNEL_INTERRUPT_H
