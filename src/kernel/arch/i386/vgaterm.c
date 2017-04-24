//
// Created by mafn on 2/4/17.
//

#include <kernel/vgaterm.h>
#include <kernel/numerics.h>
#include "vga.h"

volatile uint16_t* _video_mem = (volatile uint16_t*) 0xB8000;

struct chardev vgaterm = {
    .putc = vgaterm_putchar
};

void vgaterm_init()
{
    _video_mem_row = 0;
    _video_mem_column = 0;

    vgaterm_setcolour(get_vga_colour_entry(VGA_WHITE, VGA_BLUE));
    vgaterm_clear();
}

void vgaterm_clear()
{
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        _vgaterm_clear_row(y);
    }
}


void _vgaterm_clear_row(size_t row)
{
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        size_t video_mem_index = _get_video_mem_index(x, row);
        _video_mem[video_mem_index] = get_vga_entry(' ', _video_mem_colour);
    }
}

void vgaterm_setcolour(uint8_t colour)
{
    _video_mem_colour = colour;
}

void vgaterm_put(char to_write, uint8_t colour, size_t x, size_t y)
{
    size_t target_index = _get_video_mem_index(x, y);
    _video_mem[target_index] = get_vga_entry((unsigned char)to_write, colour);
}

void vgaterm_putchar(char to_write)
{
    if (to_write == '\n') {
        _video_mem_column = 0;
        _vgaterm_inc_row();
    } else {
        vgaterm_put(to_write, _video_mem_colour, _video_mem_column, _video_mem_row);
        _vgaterm_inc_column();
    }

    // _column and _row now point to the next position to put a character
    vgaterm_move_cursor_xy(_video_mem_column, _video_mem_row);
}

inline size_t _get_video_mem_index(size_t x, size_t y)
{
    return y * VGA_WIDTH + x;
}

void _vgaterm_inc_row()
{
    // Check if the incremented row would be more than the maximum row index
    if (_video_mem_row + 1 > VGA_HEIGHT-1) {
        _vgaterm_scroll();
    } else {
        _video_mem_row++;
    }
}

void _vgaterm_inc_column()
{
    _video_mem_column++;
    if (_video_mem_column >= VGA_WIDTH) {
        _video_mem_column = 0;

        _vgaterm_inc_row();
    }
}

void _vgaterm_scroll()
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
    _vgaterm_clear_row(VGA_HEIGHT - 1);
}

void vgaterm_move_cursor_xy(size_t x, size_t y)
{
    vgaterm_move_cursor((uint16_t)_get_video_mem_index(x, y));
}

void vgaterm_move_cursor(uint16_t index)
{
    vga_write_register(VGA_REG_CURSORPOS_H, U16_HIGH(index));
    vga_write_register(VGA_REG_CURSORPOS_L, U16_LOW(index));
}
