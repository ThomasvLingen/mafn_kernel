//
// Created by mafn on 2/4/17.
//

#include <kernel/mafn_term.h>
#include "mafn_vga.h"

volatile uint16_t* _video_mem = (volatile uint16_t*) 0xB8000;

struct chardev vgaterm = {
    .putc = mafn_term_putchar
};

void mafn_term_init()
{
    _video_mem_row = 0;
    _video_mem_column = 0;

    mafn_term_setcolour(get_vga_colour_entry(VGA_WHITE, VGA_BLUE));
    mafn_term_clear();
}

void mafn_term_clear()
{
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        _mafn_term_clear_row(y);
    }
}


void _mafn_term_clear_row(size_t row)
{
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        size_t video_mem_index = _get_video_mem_index(x, row);
        _video_mem[video_mem_index] = get_vga_entry(' ', _video_mem_colour);
    }
}

void mafn_term_setcolour(uint8_t colour)
{
    _video_mem_colour = colour;
}

void mafn_term_put(char to_write, uint8_t colour, size_t x, size_t y)
{
    size_t target_index = _get_video_mem_index(x, y);
    _video_mem[target_index] = get_vga_entry((unsigned char)to_write, colour);
}

void mafn_term_putchar(char to_write)
{
    if (to_write == '\n') {
        _video_mem_column = 0;
        _mafn_term_inc_row();

        return;
    }

    mafn_term_put(to_write, _video_mem_colour, _video_mem_column, _video_mem_row);
    _mafn_term_inc_column();
}

inline size_t _get_video_mem_index(size_t x, size_t y)
{
    return y * VGA_WIDTH + x;
}

void _mafn_term_inc_row()
{
    // Check if the incremented row would be more than the maximum row index
    if (_video_mem_row + 1 > VGA_HEIGHT-1) {
        _mafn_term_scroll();
    } else {
        _video_mem_row++;
    }
}

void _mafn_term_inc_column()
{
    _video_mem_column++;
    if (_video_mem_column >= VGA_WIDTH) {
        _video_mem_column = 0;

        _mafn_term_inc_row();
    }
}

void _mafn_term_scroll()
{
    // Move everything one row upwards
    for (size_t row = 1; row < VGA_HEIGHT; row++) {
        for (size_t column = 0; column < VGA_WIDTH; column++) {
            size_t source_index = _get_video_mem_index(column, row);
            size_t target_index = _get_video_mem_index(column, row-1);

            _video_mem[target_index] = _video_mem[source_index];
        }
    }

    // Clear bottom row
    _mafn_term_clear_row(VGA_HEIGHT-1);
}
