//
// Created by mafn on 3/11/17.
//
#include <kernel/print.h>
#include <kernel/chardev.h>
#include <kernel/vgaterm.h>

void k_puts(const char* str)
{
    chardev_puts(str, &vgaterm);
}

void k_putc(const char c)
{
    chardev_putc(c, &vgaterm);
}
