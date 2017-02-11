//
// Created by mafn on 2/4/17.
//

#include <stdbool.h>

#include <kernel/mafn_term.h>

void kernel_main()
{
    mafn_term_init();

    mafn_term_write_s("Booting my kernel\n");

    mafn_term_write_s("Entering infinite loop\n");

    while (true) {
        asm("nop");
    }
};
