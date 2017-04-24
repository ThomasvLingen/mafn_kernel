//
// Created by mafn on 4/9/17.
//

#ifndef MAFN_KERNEL_SERIAL_PORTS_H
#define MAFN_KERNEL_SERIAL_PORTS_H

#include <kernel/chardev.h>
#include <stdint.h>

typedef enum SERIAL_PORTS
{
    SERIAL_COM1 = 0x03F8,
    SERIAL_COM2 = 0x02F8,
    SERIAL_COM3 = 0x03E8,
    SERIAL_COM4 = 0x02E8
} serial_port_t;

typedef enum SERIAL_BAUD_RATE
{
    BAUD_115200 = 1,
    BAUD_57600  = 2,
    BAUD_38400  = 3,
    BAUD_19200  = 6,
    BAUD_9600   = 12,
    BAUD_4800   = 24,
    BAUD_2400   = 48,
    BAUD_1200   = 96,
    BAUD_300    = 384,
    BAUD_110    = 1047
} serial_baud_t;

typedef enum SERIAL_DATA
{
    DATA_5BIT = 0,
    DATA_6BIT = 1,
    DATA_7BIT = 2,
    DATA_8BIT = 3
} serial_data_t;

typedef enum SERIAL_STOP
{
    STOP_1 = 0,
    STOP_2 = 1
} serial_stop_t;

typedef enum SERIAL_PARITY
{
    PARITY_NONE = 0,
    PARITY_ODD = 1,
    PARITY_EVEN = 3,
    PARITY_MARK = 5,
    PARITY_SPACE = 7
} serial_parity_t;

#define SERIAL_BITS_DATA(bits)   (uint8_t)(bits << 0)
#define SERIAL_BITS_STOP(bits)   (uint8_t)(bits << 2)
#define SERIAL_BITS_PARITY(bits) (uint8_t)(bits << 3)

struct simple_serial_port
{
    serial_baud_t   baud_rate;
    serial_data_t   data_bits;
    serial_stop_t   stop_bits;
    serial_parity_t parity;
};

// Serial port registers
// Divisor access bit == 0
#define SERIAL_R_DATA 0
#define SERIAL_R_INT_ENABLE 1
// Divisor access bit == 1
#define SERIAL_R_DIV_L 0
#define SERIAL_R_DIV_H 1
#define SERIAL_R_INT_IDENT_FIFO_CTRL 2
#define SERIAL_R_LINE_CTRL 3
#define SERIAL_R_MODEM_CTRL 4
#define SERIAL_R_LINE_STATUS 5
// Serial port data bits
#define SERIAL_D_DLAB(bit) (uint8_t)(bit << 7)
#define SERIAL_D_TRANSMIT_EMPTY(bit) (uint8_t)(bit << 5)

extern struct chardev serial_COM1;

extern void serial_init();
extern void serial_init_port(serial_port_t port, struct simple_serial_port settings);
extern void serial_putc(serial_port_t port, char c);

#endif //MAFN_KERNEL_SERIAL_PORTS_H
