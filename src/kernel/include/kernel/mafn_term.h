//
// Created by mafn on 2/4/17.
//

#ifndef MAFN_KERNEL_MAFN_TERM_HPP
#define MAFN_KERNEL_MAFN_TERM_HPP

#include <stddef.h>
#include <stdint.h>

#include <kernel/chardev.h>

volatile uint16_t* _video_mem;

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t _video_mem_row;
size_t _video_mem_column;
uint8_t _video_mem_colour;

void mafn_term_init();
void mafn_term_setcolour(uint8_t colour);
void mafn_term_put(char to_write, uint8_t colour, size_t x, size_t y);
void mafn_term_putchar(char to_write);
void mafn_term_clear();

void _mafn_term_clear_row(size_t row);
void _mafn_term_inc_row();
void _mafn_term_inc_column();
void _mafn_term_scroll();

size_t _get_video_mem_index(size_t x, size_t y);

extern struct chardev vgaterm;

#endif //MAFN_KERNEL_MAFN_TERM_HPP
