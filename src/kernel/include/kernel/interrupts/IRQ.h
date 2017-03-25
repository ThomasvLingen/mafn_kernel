//
// Created by mafn on 3/19/17.
//

#ifndef MAFN_KERNEL_IRQ_H
#define MAFN_KERNEL_IRQ_H

#include <kernel/interrupts/ISR.h>
#include <kernel/funptr.h>
#include <kernel/print.h>

#define HW_IRQ_HANDLERS 16

// 0-31 are taken up by CPU exceptions
#define MAFN_KERNEL_IRQ_START 32

typedef __FUNPTR(void, irq_handler_fn, (void));
extern irq_handler_fn hw_irq_handlers[HW_IRQ_HANDLERS];

extern void _mafn_kernel_irq_handler(struct isr_regs regs);

extern void irq_init();
extern void irq_install_handler(uint8_t irq, irq_handler_fn to_install);
extern void irq_uninstall(uint8_t irq);

// Hardware IRQ handlers --> defined in IRQ_asm.s

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

#endif //MAFN_KERNEL_IRQ_H
