//
// Created by mafn on 4/9/17.
//

#include <kernel/drivers/serial_ports.h>

#include <kernel/asm/io.h>
#include <kernel/numerics.h>
#include <stdbool.h>

static void _COM1_putc(char c);
static void _COM2_putc(char c);
static void _COM3_putc(char c);
static void _COM4_putc(char c);
static void _serial_write_reg(serial_port_t port, uint8_t reg, uint8_t value);
static uint8_t _serial_read_reg(serial_port_t port, uint8_t reg);
static uint8_t _serial_get_line_ctrl(uint8_t data_bits, uint8_t stop_bit, uint8_t parity);

struct chardev serial_COM1 = {
    .putc = _COM1_putc
};

void serial_init()
{
    struct simple_serial_port COM1 = {
        .baud_rate = BAUD_38400,
        .data_bits = DATA_8BIT,
        .stop_bits = STOP_1,
        .parity = PARITY_NONE
    };

    serial_init_port(SERIAL_COM1, COM1);
}

static bool _is_transmit_empty(serial_port_t port)
{
    return (_serial_read_reg(port, SERIAL_R_LINE_STATUS) & SERIAL_D_TRANSMIT_EMPTY(1)) > 0;
}

void serial_putc(serial_port_t port, char c)
{
    while (!_is_transmit_empty(port)) {
        // Wait...
    }

    _serial_write_reg(port, SERIAL_R_DATA, c);
}

void serial_init_port(serial_port_t port, struct simple_serial_port settings)
{
    uint16_t baud_rate = (uint16_t) settings.baud_rate;
    uint8_t line_ctrl = _serial_get_line_ctrl(settings.data_bits, settings.stop_bits, settings.parity);

    _serial_write_reg(port, SERIAL_R_INT_ENABLE, 0x00);
    _serial_write_reg(port, SERIAL_R_LINE_CTRL, SERIAL_D_DLAB(1));
    _serial_write_reg(port, SERIAL_R_DIV_L, U16_LOW(baud_rate));
    _serial_write_reg(port, SERIAL_R_DIV_H, U16_HIGH(baud_rate));
    _serial_write_reg(port, SERIAL_R_LINE_CTRL, line_ctrl);

    _serial_write_reg(port, SERIAL_R_INT_IDENT_FIFO_CTRL, 0xC7); // Magic number from OSDev wiki (Enable FIFO, Clear, 14 byte threshold)
    _serial_write_reg(port, SERIAL_R_MODEM_CTRL, 0x0B);          // Magic number from OSDev wiki (IRQs enabled, RTS/DST set)
}

static void _serial_write_reg(serial_port_t port, uint8_t reg, uint8_t value)
{
    outb(port + reg, value);
}

static uint8_t _serial_read_reg(serial_port_t port, uint8_t reg)
{
    return inb(port + reg);
}

static uint8_t _serial_get_line_ctrl(uint8_t data_bits, uint8_t stop_bit, uint8_t parity)
{
    uint8_t line_ctrl = 0;

    line_ctrl |= SERIAL_BITS_DATA(data_bits);
    line_ctrl |= SERIAL_BITS_STOP(stop_bit);
    line_ctrl |= SERIAL_BITS_PARITY(parity);

    return line_ctrl;
}

static void _COM1_putc(char c)
{
    serial_putc(SERIAL_COM1, c);
}
