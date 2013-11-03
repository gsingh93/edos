#include "assert.h"
#include "defs.h"
#include "idt.h"
#include "irq.h"
#include "pic.h"
#include "portio.h"
#include "screen.h"

extern idt_function irq0;
extern idt_function irq1;
extern idt_function irq2;
extern idt_function irq3;
extern idt_function irq4;
extern idt_function irq5;
extern idt_function irq6;
extern idt_function irq7;
extern idt_function irq8;
extern idt_function irq9;
extern idt_function irq10;
extern idt_function irq11;
extern idt_function irq12;
extern idt_function irq13;
extern idt_function irq14;
extern idt_function irq15;

static pic_t master;
static pic_t slave;

/*
 * We don't want to overwrite existing entries in the IDT, so we remap the IRQ
 * numbers for the master and slave PIC by sending initialization control words
 * (ICWs). See http://www.brokenthorn.com/Resources/OSDevPic.html
 */
static void remap_irqs() {
    PIC_send_command(&master, ICW1_INIT | ICW1_ICW4);
    PIC_send_command(&slave, ICW1_INIT | ICW1_ICW4);

    PIC_send_data(&master, 0x20); // IRQs start at 32
    PIC_send_data(&master, 0x04); // Slave is at IRQ 2
    PIC_send_data(&master, 0x01);
    PIC_send_data(&master, 0x0);

    PIC_send_data(&slave, 0x28); // IRQs start at 40
    PIC_send_data(&slave, 0x02); // Cascade identity
    PIC_send_data(&slave, 0x01);
    PIC_send_data(&slave, 0x0);
}

void init_irqs() {
    PIC_init(&master, MASTER);
    PIC_init(&slave, SLAVE);
    remap_irqs();
    idt_create_descriptor(32, irq0, 0xE);
    idt_create_descriptor(33, irq1, 0xE);
    idt_create_descriptor(34, irq2, 0xE);
    idt_create_descriptor(35, irq3, 0xE);
    idt_create_descriptor(36, irq4, 0xE);
    idt_create_descriptor(37, irq5, 0xE);
    idt_create_descriptor(38, irq6, 0xE);
    idt_create_descriptor(39, irq7, 0xE);
    idt_create_descriptor(40, irq8, 0xE);
    idt_create_descriptor(41, irq9, 0xE);
    idt_create_descriptor(42, irq10, 0xE);
    idt_create_descriptor(43, irq11, 0xE);
    idt_create_descriptor(44, irq12, 0xE);
    idt_create_descriptor(45, irq13, 0xE);
    idt_create_descriptor(46, irq14, 0xE);
    idt_create_descriptor(47, irq15, 0xE);
}

void irq_handler(interrupt_stack_frame_t frame) {
    ASSERT_INTERRUPTS_DISABLED();
    if (frame.interrupt_number > 40) {
        // Reset slave
        PIC_send_command(&slave, 0x20);
    }

    // Reset master
    PIC_send_command(&master, 0x20);

    if (interrupt_handlers[frame.interrupt_number] != NULL) {
        interrupt_handler *handler = interrupt_handlers[frame.interrupt_number];
        handler(frame);
    }
}
