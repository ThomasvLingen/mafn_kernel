//
// Created by mafn on 3/25/17.
//

#include <kernel/drivers/ps2_keyboard.h>
#include <kernel/drivers/ps2_scancodes.h>

#include <kernel/interrupts/IRQ.h>
#include <kernel/asm/io.h>

uint8_t ps2_keyboard_status = 0x00;

static uint8_t _get_mod_bit(keyboard_keys_t key)
{
    if (!key_is_modifier(key)) {
        return 0;
    }

    uint8_t shift = key - 0x80;

    return (uint8_t)(1 << shift);
}

void ps2_keyboard_init()
{
    irq_install_handler(1, ps2_keyboard_handler);
}

static inline bool _is_released(uint8_t scancode)
{
    return (scancode & 0x80) > 0;
}

void ps2_keyboard_handler(void)
{
    uint8_t scancode = inb(PS2_KEYBOARD_R_DATA);
    bool was_released = _is_released(scancode);
    keyboard_keys_t key = get_key(scancode, was_released);

    if (was_released) {
        if (key_is_modifier(key)) {
            // Pulls a bit to 0
            ps2_keyboard_status &= ~(_get_mod_bit(key));
        }
    } else {
        if (key_is_modifier(key)) {
            // Pulls a bit to 1
            ps2_keyboard_status |= _get_mod_bit(key);
        } else {
            char c = get_ascii(key);

            if (c) {
                k_putc(c);
            }
        }
    }
}

bool ps2_mod_shift()
{
    uint8_t mod_shift_mask = _get_mod_bit(KEY_LSHIFT) | _get_mod_bit(KEY_RSHIFT);

    return (ps2_keyboard_status & mod_shift_mask) > 0;
}

bool ps2_mod_ctrl()
{
    uint8_t mod_ctrl_mask = _get_mod_bit(KEY_LCTRL) | _get_mod_bit(KEY_RCTRL);

    return (ps2_keyboard_status & mod_ctrl_mask) > 0;
}

bool ps2_mod_alt()
{
    uint8_t mod_alt_mask = _get_mod_bit(KEY_LALT) | _get_mod_bit(KEY_RALT);

    return (ps2_keyboard_status & mod_alt_mask) > 0;
}
