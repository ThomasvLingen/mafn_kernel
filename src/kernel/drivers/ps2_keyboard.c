//
// Created by mafn on 3/25/17.
//

#include <kernel/drivers/ps2_keyboard.h>
#include <kernel/drivers/ps2_scancodes.h>

#include <kernel/interrupts/IRQ.h>
#include <kernel/asm/io.h>

uint8_t ps2_keyboard_status = 0x00;

char ps2_keyboard_ascii_buffer[PS2_KEYBOARD_BUFFER_SIZE] = { 0 };
bool ps2_keyboard_keys_pressed[UINT8_MAX] = { 0 };

uint8_t ascii_buffer_head_i = 0;
uint8_t ascii_buffer_tail_i = 0;

static uint8_t _get_mod_bit(keyboard_keys_t key)
{
    if (!key_is_modifier(key)) {
        return 0;
    }

    uint8_t shift = key - 0x80;

    return (uint8_t)(1 << shift);
}

static void _ascii_buffer_push(char to_add)
{
    if (to_add) {
        ps2_keyboard_ascii_buffer[ascii_buffer_head_i] = to_add;

        ascii_buffer_head_i++;
    }
}

static char _ascii_buffer_pop()
{
    char to_return = ps2_keyboard_ascii_buffer[ascii_buffer_tail_i];

    ascii_buffer_tail_i++;

    return to_return;
}


void ps2_keyboard_init()
{
    irq_install_handler(1, ps2_keyboard_handler);
}

static inline bool _is_released(uint8_t scancode)
{
    return (scancode & 0x80) > 0;
}

static void _handle_mod_keys(keyboard_keys_t key, bool released)
{
    if (released) {
        // Pulls a bit to 0
        ps2_keyboard_status &= ~(_get_mod_bit(key));
    } else {
        // Pulls a bit to 1
        ps2_keyboard_status |= _get_mod_bit(key);
    }
}

void ps2_keyboard_handler(void)
{
    uint8_t scancode = inb(PS2_KEYBOARD_R_DATA);
    bool was_released = _is_released(scancode);
    keyboard_keys_t key = get_key(scancode, was_released);

    if (key_is_modifier(key)) {
        _handle_mod_keys(key, was_released);
        return;
    }

    if (!was_released) {
        _ascii_buffer_push(get_ascii(key));
        ps2_keyboard_keys_pressed[key] = true;
    } else {
        ps2_keyboard_keys_pressed[key] = false;
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

bool ps2_hasc()
{
    return ascii_buffer_head_i != ascii_buffer_tail_i;
}

char ps2_getc()
{
    return _ascii_buffer_pop();
}
