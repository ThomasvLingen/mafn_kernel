//
// Created by mafn on 3/4/17.
//

#include <kernel/chardev.h>
#include <string.h>

void chardev_putc(const char to_write, struct chardev* dev)
{
    dev->putc(to_write);
}
