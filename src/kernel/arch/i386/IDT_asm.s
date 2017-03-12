# Exception handling stuff, mostly the same as Bran's kdev tutorial
.intel_syntax noprefix
.set MAFN_KERNEL_DATA_SEG, 0x0010

# Individual exceptions
.global exception0
.type exception0, @function
exception0:
    cli                # Make sure our exception handler doesn't get interrupted
    push 0             # Push an error code (which is bogus)
    push 0             # Push the IRQ number
    jmp common_isr_end # Jump to common ISR end

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

.global idt_install
.type global, @function
idt_install:
    mov eax, [esp+4]                    # Pop IDT addr off stack
    lidt [eax]                         # Load the new IDT
    ret
