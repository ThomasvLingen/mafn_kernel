//
// Created by mafn on 2/4/17.
//

#include <stdint.h>

#ifndef MAFN_KERNEL_MAFN_VGA_H
#define MAFN_KERNEL_MAFN_VGA_H

// VGA I/O ports
#define VGA_PORT_INDEX 0x3D4
#define VGA_PORT_VALUE 0x3D5

// VGA register indexes
#define VGA_REG_CURSORPOS_H 14
#define VGA_REG_CURSORPOS_L 15

typedef enum vga_colour {
    VGA_BLACK = 0,
    VGA_BLUE = 1,
    VGA_GREEN = 2,
    VGA_CYAN = 3,
    VGA_RED = 4,
    VGA_MAGENTA = 5,
    VGA_BROWN = 6,
    VGA_LIGHT_GREY = 7,
    VGA_DARK_GREY = 8,
    VGA_LIGHT_BLUE = 9,
    VGA_LIGHT_GREEN = 10,
    VGA_LIGHT_CYAN = 11,
    VGA_LIGHT_RED = 12,
    VGA_LIGHT_MAGENTA = 13,
    VGA_LIGHT_BROWN = 14,
    VGA_WHITE = 15,
} VGA_colour;

uint8_t get_vga_colour_entry(VGA_colour text, VGA_colour bg);
uint16_t get_vga_entry(unsigned char c, uint8_t colour);
void vga_write_register(uint8_t reg_index, uint8_t value);

#endif //MAFN_KERNEL_MAFN_VGA_H
