global get_eflags
global clear_interrupts
global set_interrupts

get_eflags:
    pushf
    pop eax
    ret

clear_interrupts:
    cli
    ret

set_interrupts:
    sti
    ret
