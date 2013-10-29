#include "gdt.h"
#include "idt.h"
#include "screen.h"
#include "pit.h"
#include "util_asm.h"
#include "assert.h"

int kmain() {
    cls();
    init_gdt();
    init_idt();
    init_timer(50);
    set_interrupts();
    ASSERT_INTERRUPTS_ENABLED();
    puts("Hello World!\n");
    return 0;
}
