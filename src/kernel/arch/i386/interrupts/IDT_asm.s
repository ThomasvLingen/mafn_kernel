# Installer for an IDT
.intel_syntax noprefix

.global idt_install
.type global, @function
idt_install:
    mov eax, [esp+4]                    # Pop IDT addr off stack
    lidt [eax]                         # Load the new IDT
    ret
