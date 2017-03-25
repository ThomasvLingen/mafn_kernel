//
// Created by mafn on 3/25/17.
//

#include <kernel/drivers/ps2_keyboard.h>
#include "ps2_scancodes.h"

#include <kernel/interrupts/IRQ.h>
#include <kernel/asm/io.h>
#include <stdbool.h>

void ps2_keyboard_init()
{
    set_ps2_keyboard_layout(scancodes_ascii_us);

    irq_install_handler(1, ps2_keyboard_handler);
}

static inline bool _is_released(uint8_t scancode)
{
    return (scancode & 0x80) > 0;
}

void ps2_keyboard_handler(void)
{
    uint8_t scancode = inb(PS2_KEYBOARD_R_DATA);

    if (_is_released(scancode)) {
        // Do something
    } else {
        // TODO: This is for debugging purposes only, probably want to store this somewhere...
        k_putc(get_ascii(scancode));
    }
}
