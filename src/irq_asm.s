; First parameter is IRQ number, second is IDT entry number
%macro IRQ 2
    global irq%1
    irq%1:
        cli
        push 0
        push %2
        jmp irq_common_stub
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

extern irq_handler ; Defined in irq.c

irq_common_stub:
    pusha              ; Push all general purpose registers

    push ds            ; Push all data segment registers
    push es
    push fs
    push gs

    mov ax, 0x10       ; Load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler   ; Handle the IRQ

    pop gs             ; Restore all regs modified in this function
    pop fs
    pop es
    pop ds

    popa
    add esp, 8         ; Cleans up the stack
    iret               ; Return from interrupt
