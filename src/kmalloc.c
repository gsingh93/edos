#include "defs.h"
#include "kmalloc.h"

static uint32_t _kmalloc(uint32_t size, bool align);
static inline bool is_page_aligned(uint32_t addr);

// Defined in linker.ld
extern uint32_t end;
uint32_t heap_top = (uint32_t) &end;

uint32_t kmalloc(uint32_t size) {
    return _kmalloc(size, false);
}

uint32_t kmalloc_a(uint32_t size) {
    return _kmalloc(size, true);
}

static uint32_t _kmalloc(uint32_t size, bool align) {
    if (align && !is_page_aligned(heap_top)) {
        heap_top &= ~0xFFF;
        heap_top += 0x1000;
    }
    uint32_t tmp = heap_top;
    heap_top += size;
    return tmp;
}

static inline bool is_page_aligned(uint32_t addr) {
    return (addr & 0xFFF) == 0;
}
