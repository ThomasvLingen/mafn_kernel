//
// Created by mafn on 3/11/17.
//
#include <kernel/print.h>
#include <kernel/chardev.h>
#include <kernel/vgaterm.h>
#include <kernel/drivers/serial_ports.h>

#include <string.h>

static void k_writes(const char* str, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        k_putc(str[i]);
    }
}

void k_puts(const char* str)
{
    k_writes(str, strlen(str));
}

void k_putc(const char c)
{
    chardev_putc(c, &vgaterm);
    chardev_putc(c, &serial_COM1);
}
