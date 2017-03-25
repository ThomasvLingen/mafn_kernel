//
// Created by mafn on 3/19/17.
//

#include <kernel/interrupts/IRQ.h>

#include <stdbool.h>

#include <kernel/interrupts/PIC.h>
#include <kernel/interrupts/ISR.h>
#include <kernel/GDT.h>

irq_handler_fn hw_irq_handlers[HW_IRQ_HANDLERS] = { 0 };

#define ADD_IRQ(IRQ_N) mafn_kernel_idt_add_entry( \
    IRQ_N + 32, \
    (struct easy_IDT_entry) { \
        .base = irq ## IRQ_N, \
        .segment_selector = MAFN_KERNEL_CODE_SEGMENT, \
        .type = GATE_32_INT, .attr = ATTR_KERNEL \
    } \
)

void irq_init()
{
    // Remap IRQs
    init_pic(MAFN_KERNEL_IRQ_START);

    ADD_IRQ(0);
    ADD_IRQ(1);
    ADD_IRQ(2);
    ADD_IRQ(3);
    ADD_IRQ(4);
    ADD_IRQ(5);
    ADD_IRQ(6);
    ADD_IRQ(7);
    ADD_IRQ(8);
    ADD_IRQ(9);
    ADD_IRQ(10);
    ADD_IRQ(11);
    ADD_IRQ(12);
    ADD_IRQ(13);
    ADD_IRQ(14);
    ADD_IRQ(15);
}

void irq_install_handler(uint8_t irq, irq_handler_fn to_install)
{
    hw_irq_handlers[irq] = to_install;
}

void irq_uninstall(uint8_t irq)
{
    hw_irq_handlers[irq] = 0;
}

inline static bool _is_hw_irq_interrupt(uint32_t interrupt_i)
{
    return interrupt_i > 0 && interrupt_i < HW_IRQ_HANDLERS;
}

void _mafn_kernel_irq_handler(struct isr_regs regs)
{
    if (_is_hw_irq_interrupt(regs.interrupt_i)) {
        irq_handler_fn handler = hw_irq_handlers[regs.interrupt_i];

        if (handler) {
            handler();
        }
    }

    pic_irq_ack((uint8_t)regs.interrupt_i);
}
