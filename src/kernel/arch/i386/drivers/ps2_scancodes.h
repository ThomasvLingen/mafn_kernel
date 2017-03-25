//
// Created by mafn on 3/25/17.
//

#ifndef MAFN_KERNEL_PS2_SCANCODES_H
#define MAFN_KERNEL_PS2_SCANCODES_H

#include <stdint.h>

extern char scancodes_ascii_us[128];
extern char* scancodes_ascii;

extern void set_ps2_keyboard_layout(char* new_layout);
extern char get_ascii(uint8_t scancode);

#endif //MAFN_KERNEL_PS2_SCANCODES_H
