//
// Created by mafn on 2/4/17.
//

#include <stdbool.h>

#include <kernel/print.h>
#include <kernel/vgaterm.h>
#include <kernel/GDT.h>
#include <kernel/IDT.h>

void kernel_main()
{
    vgaterm_init();

    k_puts("Booting mafn kernel\n");
    k_puts("Installing GDT...");
    mafn_kernel_gdt_init();
    k_puts(" [DONE]\n");
    k_puts("Installing IDT...");
    mafn_kernel_idt_init();
    k_puts(" [DONE]\n");

    k_puts("Entering infinite loop\n");

    while (true) {
        asm("nop");
    }
};
