//
// Created by mafn on 3/25/17.
//

#ifndef MAFN_KERNEL_PS2_SCANCODES_H
#define MAFN_KERNEL_PS2_SCANCODES_H

#include <stdint.h>
#include <stdbool.h>

typedef enum PS2_KEYS {
    // Numeric keys
    KEY_0 = 0x00, KEY_1 = 0x01, KEY_2 = 0x02, KEY_3 = 0x03, KEY_4 = 0x04,
    KEY_5 = 0x05, KEY_6 = 0x06, KEY_7 = 0x07, KEY_8 = 0x08, KEY_9 = 0x09,

    // Alphabetic keys
    KEY_A = 0x10, KEY_B = 0x11, KEY_C = 0x12, KEY_D = 0x13, KEY_E = 0x14,
    KEY_F = 0x15, KEY_G = 0x16, KEY_H = 0x17, KEY_I = 0x18, KEY_J = 0x19,
    KEY_K = 0x1A, KEY_L = 0x1B, KEY_M = 0x1C, KEY_N = 0x1D, KEY_O = 0x1E, KEY_P = 0x1F,
    KEY_Q = 0x20, KEY_R = 0x21, KEY_S = 0x22, KEY_T = 0x23, KEY_U = 0x24,
    KEY_V = 0x25, KEY_W = 0x26, KEY_X = 0x27, KEY_Y = 0x28, KEY_Z = 0x29,

    // Symbols
    KEY_MINUS     = 0x30, KEY_EQUALS   = 0x31,
    KEY_LBRACKET  = 0x32, KEY_RBRACKET = 0x33, KEY_BACKSLASH = 0x34,
    KEY_SEMICOLON = 0x35, KEY_QUOTE    = 0x36,
    KEY_COMMA     = 0x37, KEY_PERIOD   = 0x38, KEY_SLASH     = 0x39,
    KEY_SQUIGGLE  = 0x3A,

    // Keypad
    KEY_KP0 = 0x40, KEY_KP1 = 0x41, KEY_KP2 = 0x42, KEY_KP3 = 0x43, KEY_KP4 = 0x44,
    KEY_KP5 = 0x45, KEY_KP6 = 0x46, KEY_KP7 = 0x47, KEY_KP8 = 0x48, KEY_KP9 = 0x49,
    KEY_KP_PLUS = 0x4A, KEY_KP_MINUS = 0x4B, KEY_KP_STAR = 0x4C,
    KEY_KP_PERIOD = 0x4E,
    KEY_KP_NUMLK = 0x4F,

    // Function keys
    KEY_F1 = 0x60, KEY_F2 = 0x61, KEY_F3 = 0x62, KEY_F4  = 0x63, KEY_F5  = 0x64, KEY_F6  = 0x65,
    KEY_F7 = 0x66, KEY_F8 = 0x67, KEY_F9 = 0x68, KEY_F10 = 0x69, KEY_F11 = 0x6A, KEY_F12 = 0x6B,

    // Modifier keys
    KEY_LSHIFT = 0x80, KEY_LCTRL = 0x81, KEY_LALT = 0x82, KEY_LSPECIAL = 0x83,
    KEY_RSHIFT = 0x84, KEY_RCTRL = 0x85, KEY_RALT = 0x86, KEY_RSPECIAL = 0x87,

    // Misc keys
    KEY_ENTER = 0x90,
    KEY_SPACE = 0x91,
    KEY_BACKSPACE = 0x92,
    KEY_TAB = 0x93,
    KEY_INSERT = 0x94, KEY_HOME = 0x95, KEY_PGUP = 0x96,
    KEY_DELETE = 0x97, KEY_END = 0x98, KEY_PGDN = 0x99,
    KEY_ESC = 0xA0,
} keyboard_keys_t;

struct scancode_to_ascii_table {
    char normal[UINT8_MAX];
    char shift[UINT8_MAX];
};

extern bool key_is_modifier(keyboard_keys_t key);

extern struct scancode_to_ascii_table scancode_to_ascii_us;

extern keyboard_keys_t get_key(uint8_t scancode, bool released);
extern char get_ascii(keyboard_keys_t scancode);

#endif //MAFN_KERNEL_PS2_SCANCODES_H
