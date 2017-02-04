//
// Created by mafn on 2/4/17.
//

#include <stdint.h>

#ifndef MAFN_KERNEL_MAFN_VGA_H
#define MAFN_KERNEL_MAFN_VGA_H

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

#endif //MAFN_KERNEL_MAFN_VGA_H
