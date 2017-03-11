# Largely copied from Bran's kernel development tutorial, except that I pass the GDT address as a function param
.intel_syntax noprefix
.set MAFN_KERNEL_CODE_SEG, 0x0008
.set MAFN_KERNEL_DATA_SEG, 0x0010

.global gdt_flush
.type gdt_flush, @function
gdt_flush:
    mov eax, [esp+4]                       # Put the GDT address in EAX
    cli                                    # Disable interrupts to prevent the CPU from going apeshit about the fact that I'm mucking with internals
    lgdt [eax]                             # Load GDT from EAX
    jmp MAFN_KERNEL_CODE_SEG:flush_regs    # Jump into our shiny new code segment

flush_regs:
    mov ax, MAFN_KERNEL_DATA_SEG           # Put data segment index in AX
    mov bx, ax
    mov ds, ax                             # Reload segment registers with AX
    mov es, ax                             # ...
    mov fs, ax                             # ...
    mov gs, ax                             # ...
    mov ss, ax                             # ...
    ret
