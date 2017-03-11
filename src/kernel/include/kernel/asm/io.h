//
// Created by mafn on 3/4/17.
//

#ifndef MAFN_KERNEL_IO_H
#define MAFN_KERNEL_IO_H

#include <stdint.h>

static inline void outb(uint16_t port, uint8_t value)
{
    asm volatile (
        "outb %[value], %[port]"
        :
        : [value] "a" (value), [port] "Nd"(port)
    );
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t read_byte;

    asm volatile (
        "inb %[port], %[read_byte]"
        : [read_byte] "=a" (read_byte)
        : [port] "Nd" (port)
    );

    return read_byte;
}

#endif //MAFN_KERNEL_IO_H
