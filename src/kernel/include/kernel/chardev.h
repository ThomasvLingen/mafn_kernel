//
// Created by mafn on 3/4/17.
//

#ifndef MAFN_KERNEL_CHARDEV_HPP
#define MAFN_KERNEL_CHARDEV_HPP

#include <stddef.h>

#include <kernel/funptr.h>

typedef __FUNPTR(void, putc_fn, (char c));

struct chardev {
    putc_fn putc;
};

extern void chardev_write(const char* to_write, size_t size, struct chardev* dev);
extern void chardev_puts(const char* to_write, struct chardev* dev);

#endif //MAFN_KERNEL_CHARDEV_HPP
