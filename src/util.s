global get_eflags

get_eflags:
    pushf
    pop eax
    ret
