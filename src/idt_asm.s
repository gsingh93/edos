global load_idt

; Sets the IDT register to the first parameter on the stack
load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret
