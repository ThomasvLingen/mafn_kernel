//
// Created by mafn on 3/25/17.
//

#include <kernel/drivers/ps2_scancodes.h>

#include <kernel/drivers/ps2_keyboard.h>

// As seen on wiki.osdevorg/PS2_Keyboard
// This currently lacks double scancode keys such as KEY_RCTRL or KEY_RALT
keyboard_keys_t ps2_keymap_us[UINT8_MAX] = {
    [0x0B] = KEY_0, [0x02] = KEY_1, [0x03] = KEY_2, [0x04] = KEY_3, [0x05] = KEY_4,
    [0x06] = KEY_5, [0x07] = KEY_6, [0x08] = KEY_7, [0x09] = KEY_8, [0x0A] = KEY_9,

    [0x1E] = KEY_A, [0x30] = KEY_B, [0x2E] = KEY_C, [0x20] = KEY_D, [0x12] = KEY_E,
    [0x21] = KEY_F, [0x22] = KEY_G, [0x23] = KEY_H, [0x17] = KEY_I, [0x24] = KEY_J,
    [0x25] = KEY_K, [0x26] = KEY_L, [0x32] = KEY_M, [0x31] = KEY_N, [0x18] = KEY_O, [0x19] = KEY_P,
    [0x10] = KEY_Q, [0x13] = KEY_R, [0x1F] = KEY_S, [0x14] = KEY_T, [0x16] = KEY_U,
    [0x2F] = KEY_V, [0x11] = KEY_W, [0x2D] = KEY_X, [0x15] = KEY_Y, [0x2C] = KEY_Z,

    [0x0C] = KEY_MINUS,     [0x0D] = KEY_EQUALS,
    [0x1A] = KEY_LBRACKET,  [0x1B] = KEY_RBRACKET, [0x2B] = KEY_BACKSLASH,
    [0x27] = KEY_SEMICOLON, [0x28] = KEY_QUOTE,
    [0x33] = KEY_COMMA,     [0x34] = KEY_PERIOD,   [0x35] = KEY_SLASH,
    [0x29] = KEY_SQUIGGLE,

    [0x52] = KEY_KP0, [0x4F] = KEY_KP1, [0x50] = KEY_KP2, [0x51] = KEY_KP3, [0x4B] = KEY_KP4,
    [0x4C] = KEY_KP5, [0x4D] = KEY_KP6, [0x47] = KEY_KP7, [0x48] = KEY_KP8, [0x49] = KEY_KP9,
    [0x4E] = KEY_KP_PLUS, [0x4A] = KEY_KP_MINUS, [0x37] = KEY_KP_STAR,
    [0x53] = KEY_KP_PERIOD,
    [0x45] = KEY_KP_NUMLK,

    [0x3B] = KEY_F1, [0x3C] = KEY_F2, [0x3D] = KEY_F3, [0x3E] = KEY_F4 , [0x3F] = KEY_F5 , [0x40] = KEY_F6 ,
    [0x41] = KEY_F7, [0x42] = KEY_F8, [0x43] = KEY_F9, [0x44] = KEY_F10, [0x57] = KEY_F11, [0x58] = KEY_F12,

    [0x2A] = KEY_LSHIFT, [0x1D] = KEY_LCTRL, [0x38] = KEY_LALT,
    [0x36] = KEY_RSHIFT,

    [0x1C] = KEY_ENTER,
    [0x39] = KEY_SPACE,
    [0x0E] = KEY_BACKSPACE,
    [0x0F] = KEY_TAB,
    [0x01] = KEY_ESC
};

struct scancode_to_ascii_table scancode_to_ascii_us = {
    .normal = {
        [KEY_0] = '0', [KEY_1] = '1', [KEY_2] = '2', [KEY_3] = '3', [KEY_4] = '4',
        [KEY_5] = '5', [KEY_6] = '6', [KEY_7] = '7', [KEY_8] = '8', [KEY_9] = '9',

        [KEY_A] = 'a', [KEY_B] = 'b', [KEY_C] = 'c', [KEY_D] = 'd', [KEY_E] = 'e',
        [KEY_F] = 'f', [KEY_G] = 'g', [KEY_H] = 'h', [KEY_I] = 'i', [KEY_J] = 'j',
        [KEY_K] = 'k', [KEY_L] = 'l', [KEY_M] = 'm', [KEY_N] = 'n', [KEY_O] = 'o', [KEY_P] = 'p',
        [KEY_Q] = 'q', [KEY_R] = 'r', [KEY_S] = 's', [KEY_T] = 't', [KEY_U] = 'u',
        [KEY_V] = 'v', [KEY_W] = 'w', [KEY_X] = 'x', [KEY_Y] = 'y', [KEY_Z] = 'z',

        [KEY_MINUS]     = '-', [KEY_EQUALS]   = '=' ,
        [KEY_LBRACKET]  = '[', [KEY_RBRACKET] = ']' , [KEY_BACKSLASH] = '\\',
        [KEY_SEMICOLON] = ';', [KEY_QUOTE]    = '\'',
        [KEY_COMMA]     = ',', [KEY_PERIOD]   = '.' , [KEY_SLASH]     = '/' ,
        [KEY_SQUIGGLE]  = '`',

        [KEY_KP0] = '0', [KEY_KP1] = '1', [KEY_KP2] = '2', [KEY_KP3] = '3', [KEY_KP4] = '4',
        [KEY_KP5] = '5', [KEY_KP6] = '6', [KEY_KP7] = '7', [KEY_KP8] = '8', [KEY_KP9] = '9',
        [KEY_KP_PLUS] = '+', [KEY_KP_MINUS] = '-', [KEY_KP_STAR] = '*',
        [KEY_KP_PERIOD] = '.',

        [KEY_ENTER]     = '\n',
        [KEY_SPACE]     = ' ' ,
        [KEY_BACKSPACE] = '\b',
        [KEY_TAB]       = '\t',
    },
    .shift = {
        [KEY_0] = ')', [KEY_1] = '!', [KEY_2] = '@', [KEY_3] = '#', [KEY_4] = '$',
        [KEY_5] = '%', [KEY_6] = '^', [KEY_7] = '&', [KEY_8] = '*', [KEY_9] = '(',

        [KEY_A] = 'A', [KEY_B] = 'B', [KEY_C] = 'C', [KEY_D] = 'D', [KEY_E] = 'E',
        [KEY_F] = 'F', [KEY_G] = 'G', [KEY_H] = 'H', [KEY_I] = 'I', [KEY_J] = 'J',
        [KEY_K] = 'K', [KEY_L] = 'L', [KEY_M] = 'M', [KEY_N] = 'N', [KEY_O] = 'O', [KEY_P] = 'P',
        [KEY_Q] = 'Q', [KEY_R] = 'R', [KEY_S] = 'S', [KEY_T] = 'T', [KEY_U] = 'U',
        [KEY_V] = 'V', [KEY_W] = 'W', [KEY_X] = 'X', [KEY_Y] = 'Y', [KEY_Z] = 'Z',

        [KEY_MINUS]     = '_', [KEY_EQUALS]   = '+' ,
        [KEY_LBRACKET]  = '{', [KEY_RBRACKET] = ']' , [KEY_BACKSLASH] = '|',
        [KEY_SEMICOLON] = ':', [KEY_QUOTE]    = '"',
        [KEY_COMMA]     = '<', [KEY_PERIOD]   = '>' , [KEY_SLASH]     = '?' ,
        [KEY_SQUIGGLE]  = '~',

        [KEY_KP0] = '0', [KEY_KP1] = '1', [KEY_KP2] = '2', [KEY_KP3] = '3', [KEY_KP4] = '4',
        [KEY_KP5] = '5', [KEY_KP6] = '6', [KEY_KP7] = '7', [KEY_KP8] = '8', [KEY_KP9] = '9',
        [KEY_KP_PLUS] = '+', [KEY_KP_MINUS] = '-', [KEY_KP_STAR] = '*',
        [KEY_KP_PERIOD] = '.',

        [KEY_ENTER]     = '\n',
        [KEY_SPACE]     = ' ' ,
        [KEY_BACKSPACE] = '\b',
        [KEY_TAB]       = '\t',
    }
};

char get_ascii(keyboard_keys_t scancode)
{
    if (ps2_mod_shift()) {
        return scancode_to_ascii_us.shift[scancode];
    } else {
        return scancode_to_ascii_us.normal[scancode];
    }
}

keyboard_keys_t get_key(uint8_t scancode, bool released)
{
    if (released) {
        scancode -= 0x80;
    }

    return ps2_keymap_us[scancode];
}

// Certain 2-byte modifiers are not supported yet (like RALT)
bool key_is_modifier(keyboard_keys_t key)
{
    return (key >= KEY_LSHIFT && key <= KEY_LALT) || key == KEY_RSHIFT;
}
