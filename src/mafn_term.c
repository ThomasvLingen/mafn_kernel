//
// Created by mafn on 2/4/17.
//

#include "mafn_term.h"
#include "mafn_vga.h"
#include "lib/string.h"

volatile uint16_t* _video_mem = (volatile uint16_t*) 0xB8000;

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
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            size_t video_mem_index = _get_video_mem_index(x, y);
            _video_mem[video_mem_index] = get_vga_entry(' ', _video_mem_colour);
        }
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

void mafn_term_write(const char* to_write, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        mafn_term_putchar(to_write[i]);
    }
}

void mafn_term_write_s(const char* to_write)
{
    mafn_term_write(to_write, strlen(to_write));
}

void _mafn_term_inc_row()
{
    _video_mem_row++;
    if (_video_mem_row > VGA_HEIGHT) {
        _video_mem_row = 0;
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
