#include "gdt.h"
#include "idt.h"
#include "screen.h"
#include "pit.h"

int kmain() {
    asm("sti");
    cls();
    init_gdt();
    init_idt();
    init_timer(50);
    puts("Hello World!\n");
    return 0;
}
