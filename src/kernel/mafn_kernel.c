//
// Created by mafn on 2/4/17.
//

#include <stdbool.h>

#include <kernel/vgaterm.h>
#include <kernel/GDT.h>

void kernel_main()
{
    vgaterm_init();

    chardev_puts("Booting mafn kernel\n", &vgaterm);
    chardev_puts("Initting GDT...", &vgaterm);
    mafn_kernel_gdt_init();
    chardev_puts(" [DONE]\n", &vgaterm);

    chardev_puts("Entering infinite loop\n", &vgaterm);

    while (true) {
        asm("nop");
    }
};
