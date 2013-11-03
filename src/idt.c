#include "defs.h"
#include "idt.h"
#include "irq.h"
#include "isr.h"
#include "screen.h"
#include "string.h"

typedef struct __attribute__((packed)) {
    unsigned offset_low  : 16;
    unsigned selector    : 16;
    unsigned unused0     : 8;
    unsigned type        : 4;
    unsigned system      : 1;
    unsigned privilege   : 2;
    unsigned present     : 1;
    unsigned offset_high : 16;
} idt_entry_t;

typedef struct __attribute__((packed)) {
    uint16_t limit;
    uint32_t base;
} idt_ptr_t;

extern void load_idt(idt_ptr_t *ip);

// Enum constant so we can use it as an array size
enum { MAX_IDT_ENTRIES = 256 };

static idt_entry_t idt[MAX_IDT_ENTRIES];
static idt_ptr_t ip;

interrupt_handler *interrupt_handlers[256];

void idt_create_descriptor(uint8_t index, idt_function *idt_fn, uint8_t type) {
    uint32_t fn_addr = (uint32_t) idt_fn;
    idt[index].offset_low = fn_addr;
    idt[index].offset_high = fn_addr >> 16;

    idt[index].selector = KERNEL_CODE_SEGMENT;
    idt[index].unused0 = 0;

    idt[index].type = type;
    idt[index].system = 0;    // 0 means this is an interrupt gate
    idt[index].privilege = 0; // Requires kernel level privilege
    idt[index].present = 1;   // Obviously this descriptor is present
}

void init_idt(void) {
    ip.base = (uint32_t) idt;
    ip.limit = (sizeof (idt_entry_t)) * MAX_IDT_ENTRIES - 1;

    init_isrs();
    init_irqs();

    load_idt(&ip); // Set IDTR to our IDT
    puts("IDT Initialized\n");
}

void register_interrupt_handler(uint8_t index, interrupt_handler *handler) {
    interrupt_handlers[index] = handler;
}
