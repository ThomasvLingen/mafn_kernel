//
// Created by mafn on 2/4/17.
//

#include <stdbool.h>

#include <kernel/mafn_term.h>

void kernel_main()
{
    mafn_term_init();

    chardev_puts("Booting my kernel\n", &vgaterm);
    chardev_puts("Entering infinite loop\n", &vgaterm);

    while (true) {
        asm("nop");
    }
};
