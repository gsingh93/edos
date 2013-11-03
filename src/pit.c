#include "assert.h"
#include "idt.h"
#include "irq.h"
#include "pic.h"
#include "pit.h"
#include "portio.h"
#include "screen.h"

#define PIT_COMMAND_PORT 0x43
#define PIT_CHANNEL_ZERO 0x40

static int tick = 0;

static void timer_callback(interrupt_stack_frame_t frame) {
    ASSERT_INTERRUPTS_DISABLED();
    tick++;
}

void init_timer(uint32_t frequency) {
    register_interrupt_handler(IRQ0, timer_callback);

    // PIT frequency is 1193180 Hz
    uint32_t divisor = 1193180 / frequency;

    outb(PIT_COMMAND_PORT, 0x36);   // Set PIT to repeating mode and tell it
                                    // that we will be setting the divisor

    // Send diviser to PIT
    uint8_t l = divisor;
    uint8_t h = divisor >> 8;
    outb(PIT_CHANNEL_ZERO, l);
    outb(PIT_CHANNEL_ZERO, h);

    puts("PIT Initialized\n");
}
