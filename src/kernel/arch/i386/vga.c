//
// Created by mafn on 2/4/17.
//

#include <kernel/asm/io.h>
#include "vga.h"

inline uint8_t get_vga_colour_entry(VGA_colour text, VGA_colour bg)
{
    return text | bg << 4;
}

inline uint16_t get_vga_entry(unsigned char c, uint8_t colour)
{
    return (uint16_t)c | (uint16_t) colour << 8;
}

void vga_write_register(uint8_t reg_index, uint8_t value)
{
    outb(VGA_PORT_INDEX, reg_index);
    outb(VGA_PORT_VALUE, value);
}
