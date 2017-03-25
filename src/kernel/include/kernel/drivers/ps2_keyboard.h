//
// Created by mafn on 3/25/17.
//

#ifndef MAFN_KERNEL_PS2_KEYBOARD_H
#define MAFN_KERNEL_PS2_KEYBOARD_H

#define PS2_KEYBOARD_R_DATA 0x60
#define PS2_KEYBOARD_R_CTRL 0x64

extern void ps2_keyboard_init();
extern void ps2_keyboard_handler(void);

#endif //MAFN_KERNEL_PS2_KEYBOARD_H
