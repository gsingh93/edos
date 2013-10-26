global load_gdt

load_gdt:
    mov eax, [esp + 4] ; Pointer to gdt_ptr is first param
    lgdt [eax]
    mov ax, 0x10       ; x86 won't let us load immediate values into
                       ; segment registers, so we have to use another
                       ; register

    mov ds, ax         ; Set all data registers to use the
    mov es, ax         ; kernel level data descriptor
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:flush_ret ; We can't set the CS register directly,
                       ; so we have to jump there to set it to
                       ; the kernel code descriptor
flush_ret:
    ret
