//
// Created by mafn on 3/25/17.
//

#include "ps2_scancodes.h"

#include <stdint.h>

// As nicked directly from Bran's kernel development tutorial, adding only a few more comments
char scancodes_ascii_us[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8',      // 0-9
    '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', // 10-19 (\b = backspace, \t = tab)
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,    // 20-29 (\n = enter, 0 = ctrl)
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',   // 30-39
    '\'', '`',   0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', // 40-49 (0 = left shift)
    'm', ',', '.', '/', 0, '*',                         // 50-55 (0 = right shift)
    0,   // 56 (left alt)
    ' ', // 57 (space bar)
    0,   // 58 (caps-lock)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                       // 59-68 (F1-F10)
    0,   // 69 (num-lock)
    0,   // 70 (scroll-lock)
    0,   // 71 (home / keypad 7)
    0,   // 72 (up / keypad 8)
    0,   // 73 (page-up / keypad 9)
    '-', // 74
    0,   // 75 (left / keypad 4)
    0,   // 76 (keypad 5)
    0,   // 77 (right / keypad 6)
    '+', // 78
    0,   // 79 (end / keypad 1)
    0,   // 80 (down / keypad 2)
    0,   // 81 (page-down / keypad 3)
    0,   // 82 (insert / keypad 0)
    0,   // 83 (delete / keypad .)
    0, 0, 0,
    0,   // 87 (F11)
    0,   // 88 (F12)
    0,   // Other keys are not defined here.
};

char* scancodes_ascii = scancodes_ascii_us;

void set_ps2_keyboard_layout(char* new_layout)
{
    scancodes_ascii = new_layout;
}

char get_ascii(uint8_t scancode)
{
    return scancodes_ascii[scancode];
}
