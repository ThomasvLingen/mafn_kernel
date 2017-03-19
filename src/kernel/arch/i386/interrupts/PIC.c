//
// Created by mafn on 3/19/17.
//

#include <kernel/interrupts/PIC.h>

#include <stdbool.h>

#include <kernel/asm/io.h>

static void _pic_slave_write(uint8_t value)
{
    outb(PIC_MASTER + PIC_R_DATA, value);
}

static void _pic_master_write(uint8_t value)
{
    outb(PIC_SLAVE + PIC_R_DATA, value);
}

void init_pic(uint8_t irq_base)
{
    // Send init command
    outb(PIC_MASTER + PIC_R_COMMAND, PIC_C_INIT);
    outb(PIC_SLAVE  + PIC_R_COMMAND, PIC_C_INIT);

    // Send init byte 1 (IRQ offset)
    _pic_master_write(irq_base);
    _pic_slave_write(irq_base + (uint8_t) 0x08);

    // Send init byte 2 (Wiring)
    _pic_master_write(PIC_MASTER_D_SLAVE_IRQ);
    _pic_slave_write(PIC_SLAVE_D_SLAVE_IRQ);

    // Send init byte 3 (Environment info)
    _pic_master_write(PIC_D_ENV_X86);
    _pic_slave_write(PIC_D_ENV_X86);

    // Clear IRQ masks
    _pic_master_write(0);
    _pic_slave_write(0);
}

static bool _is_slave_irq(uint8_t irq)
{
    return irq > 7;
}

void pic_irq_ack(uint8_t irq)
{
    if (_is_slave_irq(irq)) {
        outb(PIC_MASTER + PIC_R_COMMAND, PIC_C_EOI);
        outb(PIC_SLAVE  + PIC_R_COMMAND, PIC_C_EOI);
    } else {
        outb(PIC_MASTER + PIC_R_COMMAND, PIC_C_EOI);
    }
}
