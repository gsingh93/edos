#include "gdt.h"
#include "idt.h"
#include "screen.h"

int kmain() {
    cls();
    init_gdt();
    init_idt();
    puts("Hello World!");
    return 0;
}
