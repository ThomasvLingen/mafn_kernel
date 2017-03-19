# Exception handling stuff, mostly the same as Bran's kdev tutorial
.intel_syntax noprefix
.set MAFN_KERNEL_DATA_SEG, 0x0010

# Generic 0 error code x86 exception macro
.macro error_0_exception exception_number
    .global exception\exception_number
    .type exception\exception_number, @function
    exception\exception_number:
        cli                     # Make sure our exception handler doesn't get interrupted
        push 0                  # Push an error code (which is bogus)
        push \exception_number  # Push the IRQ number
        jmp common_isr_end      # Jump to common ISR end
.endm

# Generic x86 exception that assumes an error code is already pushed
.macro no_error_exception exception_number
    .global exception\exception_number
    .type exception\exception_number, @function
    exception\exception_number:
        cli                     # Make sure our exception handler doesn't get interrupted
        push \exception_number  # Push the IRQ number
        jmp common_isr_end      # Jump to common ISR end
.endm

# Individual exceptions
error_0_exception 0
error_0_exception 1
error_0_exception 2
error_0_exception 3
error_0_exception 4
error_0_exception 5
error_0_exception 6
error_0_exception 7
no_error_exception 8
error_0_exception 9
no_error_exception 10
no_error_exception 11
no_error_exception 12
no_error_exception 13
no_error_exception 14
# According to IA32.pdf, 15 is reserved (?)
error_0_exception 16
no_error_exception 17
error_0_exception 18
error_0_exception 19
error_0_exception 20

.globl _mafn_kernel_fault_handler
common_isr_end:
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
    call _mafn_kernel_fault_handler     # Call common C processor exception handler

    pop gs                              # Restore processor state
    pop fs                              # ...
    pop es                              # ...
    pop ds                              # ...
    popad                               # ...

    add esp, 8                          # Clean up error code and IRQ number from stack
    sti                                 # Interrupts are cool again
    iret                                # Return from ISR
