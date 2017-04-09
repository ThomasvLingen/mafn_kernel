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

extern void chardev_putc(const char to_write, struct chardev* dev);

#endif //MAFN_KERNEL_CHARDEV_HPP
