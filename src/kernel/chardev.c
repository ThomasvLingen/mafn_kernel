//
// Created by mafn on 3/4/17.
//

#include <kernel/chardev.h>
#include <string.h>

void chardev_write(const char* to_write, size_t size, struct chardev* dev)
{
    for (size_t i = 0; i < size; i++) {
        dev->putc(to_write[i]);
    }
}

void chardev_puts(const char* to_write, struct chardev* dev)
{
    chardev_write(to_write, strlen(to_write), dev);
}

void chardev_putc(const char to_write, struct chardev* dev)
{
    dev->putc(to_write);
}
