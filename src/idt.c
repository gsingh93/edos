#include "idt.h"
#include "defs.h"
#include "isr.h"
#include "string.h"
#include "screen.h"

typedef struct __attribute__((packed)) {
    unsigned offset_low : 16;
    unsigned selector : 16;
    unsigned unused0 : 8;
    unsigned type : 4;
    unsigned system : 1;
    unsigned privilege : 2;
    unsigned present : 1;
    unsigned offset_high : 16;
} idt_entry_t;

typedef struct __attribute__((packed)) {
    uint16_t limit;
    uint32_t base;
} idt_ptr_t;

extern void load_idt(idt_ptr_t *ip);

enum { MAX_IDT_ENTRIES = 256 };

static idt_entry_t idt[MAX_IDT_ENTRIES];
static idt_ptr_t ip;

void idt_create_descriptor(uint8_t i, isr_function isr_fn, uint8_t type) {
    uint32_t fn_addr = (uint32_t) isr_fn;
    idt[i].offset_low = fn_addr;
    idt[i].offset_high = fn_addr >> 16;

    idt[i].selector = KERNEL_CODE_SEGMENT;
    idt[i].unused0 = 0;

    idt[i].type = type;
    idt[i].system = 0; // 0 means this is an interrupt gate
    idt[i].privilege = 0; // Requires kernel level privilege
    idt[i].present = 1; // Obviously this descriptor is present
}

void init_idt(void) {
    ip.base = (uint32_t) &idt;
    ip.limit = (sizeof (idt_entry_t)) * MAX_IDT_ENTRIES;

    init_isrs();

    load_idt(&ip); // Set GDTR to our GDT
    puts("IDT Initialized\n");
}
