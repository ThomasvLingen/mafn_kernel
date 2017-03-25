# IRQ handling stuff
.intel_syntax noprefix
.set MAFN_KERNEL_DATA_SEG, 0x0010

# Generic IRQ handler macro
.macro irq_stub irq_number
    .global irq\irq_number
    .type irq\irq_number, @function
    irq\irq_number:
        cli
        push 0
        push \irq_number
        jmp common_irq_end
.endm

# Individual IRQ handler definitions
irq_stub 0
irq_stub 1
irq_stub 2
irq_stub 3
irq_stub 4
irq_stub 5
irq_stub 6
irq_stub 7
irq_stub 8
irq_stub 9
irq_stub 10
irq_stub 11
irq_stub 12
irq_stub 13
irq_stub 14
irq_stub 15

.globl _mafn_kernel_irq_handler
common_irq_end:
    pushad                              # Save processor state [ax, cx, dx, bx, sp, bp, si, di]
    push ds                             # ...
    push es
    push fs
    push gs

    mov ax, MAFN_KERNEL_DATA_SEG        # Load kernel data segment
    mov ds, ax                          # ...
    mov es, ax                          # ...
    mov fs, ax                          # ...
    mov gs, ax                          # ...

    # Stack: [gs, fs, es, ds, edi, esi, ebp, esp, ebx, edx, ecx, eax, interrupt_index, error_code]
    call _mafn_kernel_irq_handler       # Call common C IRQ handler

    pop gs                              # Restore processor state
    pop fs                              # ...
    pop es                              # ...
    pop ds                              # ...
    popad                               # ...

    add esp, 8                          # Clean up error code and IRQ number from stack
    sti                                 # Interrupts are cool again
    iret                                # Return from ISR
