#include "gdt.h"
#include "string.h"
#include "screen.h"

typedef struct __attribute__((packed)) {
    unsigned limit_low   : 16;
    unsigned base_low    : 16;
    unsigned base_mid    : 8;
    unsigned type        : 4;
    unsigned system      : 1;
    unsigned privilege   : 2;
    unsigned present     : 1;
    unsigned limit_high  : 4;
    unsigned avail       : 1;
    unsigned longmode    : 1;
    unsigned size        : 1;
    unsigned granularity : 1;
    unsigned base_high   : 8;
} gdt_entry_t;

typedef struct __attribute__((packed)) {
    uint16_t limit;
    uint32_t base;
} gdt_ptr_t;

extern void load_gdt(gdt_ptr_t *gp);

static gdt_entry_t gdt[5];
static gdt_ptr_t gp;

static gdt_entry_t create_descriptor(uint32_t base, uint32_t limit, uint8_t DPL, uint8_t type) {
    gdt_entry_t entry;

    entry.base_low = base & 0xFFFF;
    entry.base_mid = (base >> 16) & 0xFF;
    entry.base_high = (base >> 24) & 0xFF;

    entry.limit_low = limit & 0xFFFF; // Bottom 16 bits of limit
    entry.limit_high = (limit >> 16) & 0xF; // Bits 17-20 of limit

    // Type (4 bits)
    entry.type = type & 0xF;

    // Always 1, I don't know what this is
    entry.system = 1;

    // Privelage level (2 bits)
    entry.privilege = DPL & 0x3;

    // This descriptor is obviously present, we're setting it now
    entry.present = 1;

    // We're not in longmode
    entry.longmode = 0;

    // Not available for system use (not sure what this means)
    entry.avail = 0;

    // 0 means 16 bit, 1 means 32 bit
    entry.size = 1;

    // 0 means granularity of 1 byte, 1 means 4K
    entry.granularity = 1;

    return entry;
}

void init_gdt(void) {
    gp.base = (uint32_t) gdt;
    gp.limit = (sizeof (gdt_entry_t)) * 5;

    /*
     * For the type, 0xA means Execute/Read (which makes sense for code
     * segments, and 0x2 means Read/Write (which makes sense for data
     * segments.
     */
    memset(&gdt, 0, sizeof gdt[0]); // NULL descriptor

    #define CD(type, seg) create_descriptor(0, 0xFFFFFFFF, type, seg);
    gdt[1] = CD(0, 0xA); // Kernel code segment
    gdt[2] = CD(0, 0x2); // Kernel data segment
    gdt[3] = CD(3, 0xA); // User code segment
    gdt[4] = CD(3, 0x2); // User data segment
    #undef CD

    load_gdt(&gp); // Set GDTR to our GDT
    puts("GDT Initialized\n");
}
