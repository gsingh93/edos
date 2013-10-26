#include "isr.h"
#include "idt.h"
#include "screen.h"
#include <stdint.h>

extern idt_function isr0;
extern idt_function isr1;
extern idt_function isr2;
extern idt_function isr3;
extern idt_function isr4;
extern idt_function isr5;
extern idt_function isr6;
extern idt_function isr7;
extern idt_function isr8;
extern idt_function isr9;
extern idt_function isr10;
extern idt_function isr11;
extern idt_function isr12;
extern idt_function isr13;
extern idt_function isr14;
extern idt_function isr15;
extern idt_function isr16;
extern idt_function isr17;
extern idt_function isr18;
extern idt_function isr19;
extern idt_function isr20;
extern idt_function isr21;
extern idt_function isr22;
extern idt_function isr23;
extern idt_function isr24;
extern idt_function isr25;
extern idt_function isr26;
extern idt_function isr27;
extern idt_function isr28;
extern idt_function isr29;
extern idt_function isr30;
extern idt_function isr31;

#define NUM_ISRS 32
static char *exception_messages[NUM_ISRS] = {
    "Division By Zero",
    "Debug Exception",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds Exception",
    "Invalid Opcode Exception",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved"
};

void init_isrs(void) {
    idt_create_descriptor(0, isr0, 0xE);
    idt_create_descriptor(1, isr1, 0xE);
    idt_create_descriptor(2, isr2, 0xE);
    idt_create_descriptor(3, isr3, 0xE);
    idt_create_descriptor(4, isr4, 0xE);
    idt_create_descriptor(5, isr5, 0xE);
    idt_create_descriptor(6, isr6, 0xE);
    idt_create_descriptor(7, isr7, 0xE);
    idt_create_descriptor(8, isr8, 0xE);
    idt_create_descriptor(9, isr9, 0xE);
    idt_create_descriptor(10, isr10, 0xE);
    idt_create_descriptor(11, isr11, 0xE);
    idt_create_descriptor(12, isr12, 0xE);
    idt_create_descriptor(13, isr13, 0xE);
    idt_create_descriptor(14, isr14, 0xE);
    idt_create_descriptor(15, isr15, 0xE);
    idt_create_descriptor(16, isr16, 0xE);
    idt_create_descriptor(17, isr17, 0xE);
    idt_create_descriptor(18, isr18, 0xE);
    idt_create_descriptor(19, isr19, 0xE);
    idt_create_descriptor(20, isr20, 0xE);
    idt_create_descriptor(21, isr21, 0xE);
    idt_create_descriptor(22, isr22, 0xE);
    idt_create_descriptor(23, isr23, 0xE);
    idt_create_descriptor(24, isr24, 0xE);
    idt_create_descriptor(25, isr25, 0xE);
    idt_create_descriptor(26, isr26, 0xE);
    idt_create_descriptor(27, isr27, 0xE);
    idt_create_descriptor(28, isr28, 0xE);
    idt_create_descriptor(29, isr29, 0xE);
    idt_create_descriptor(30, isr30, 0xE);
    idt_create_descriptor(31, isr31, 0xE);
}

void isr_handler(interrupt_stack_frame_t frame) {
    if (frame.interrupt_number < NUM_ISRS) {
        puts(exception_messages[frame.interrupt_number]);
        putchar('\n');
    }
}
