#include "gdt.h"
#include "idt.h"
#include "screen.h"
#include "pit.h"
#include "util_asm.h"

int kmain() {
    set_interrupts();
    cls();
    init_gdt();
    init_idt();
    init_timer(50);
    puts("Hello World!\n");
    return 0;
}
