//
// Created by mafn on 2/4/17.
//

#include "mafn_vga.h"

inline uint8_t get_vga_colour_entry(VGA_colour text, VGA_colour bg)
{
    return text | bg << 4;
}

inline uint16_t get_vga_entry(unsigned char c, uint8_t colour)
{
    return (uint16_t)c | (uint16_t) colour << 8;
}