//
// Created by mafn on 3/19/17.
//

#ifndef MAFN_KERNEL_PIC_H
#define MAFN_KERNEL_PIC_H

#include <stdint.h>

/*
 * There are actually 2 PICs in the x86 architecture
 * Master PIC
 * - IO ports:
 *       Command = 0x20
 *       Data    = 0x21
 * - Hardware IRQs 0-7
 * Slave PIC
 * - IO ports:
 *       Command = 0xA0
 *       Data    = 0xA1
 * - Hardware IRQs 8-15
 */

/*
 * In protected mode, IRQs 0-7 are by default mapped to INT 0-7, which is not nice because that conflicts with intel
 *   CPU exceptions.
 * Therefore, they have to be remapped.
 */

// PIC Address defintions
#define PIC_MASTER    0x20
#define PIC_SLAVE     0xA0
#define PIC_R_COMMAND 0
#define PIC_R_DATA    1

// PIC commands
// End of Interrupt
#define PIC_C_INIT 0x11
#define PIC_C_EOI 0x20

// PIC data
// This is in bit notation (0x4 = bit 2)
#define PIC_MASTER_D_SLAVE_IRQ (uint8_t)(1 << 2)
// This is in binary notation
#define PIC_SLAVE_D_SLAVE_IRQ 2
#define PIC_D_ENV_X86 1

extern void init_pic(uint8_t irq_base);
extern void pic_irq_ack(uint8_t irq);

#endif //MAFN_KERNEL_PIC_H
