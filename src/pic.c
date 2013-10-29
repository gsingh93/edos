#include "pic.h"
#include "portio.h"

#define PIC_READ_IRR                0x0a    /* OCW3 irq ready next CMD read   */
#define PIC_READ_ISR                0x0b    /* OCW3 irq service next CMD read */

static uint8_t PIC_read_reg(pic_t *pic, int ocw3);

void PIC_init(pic_t *pic, pic_type_t type) {
    if (type == MASTER) {
        pic->cmd_port = 0x20;
        pic->data_port = 0x21;
    } else { // type == SLAVE
        pic->cmd_port = 0xA0;
        pic->data_port = 0xA1;
    }
}

void PIC_send_command(pic_t *pic, uint8_t command) {
    outb(pic->cmd_port, command);
}

void PIC_send_data(pic_t *pic, uint8_t data) {
    outb(pic->data_port, data);
}

uint8_t PIC_get_irr(pic_t *pic) {
    return PIC_read_reg(pic, PIC_READ_IRR);
}

uint8_t PIC_get_isr(pic_t *pic) {
    return PIC_read_reg(pic, PIC_READ_ISR);
}

static uint8_t PIC_read_reg(pic_t *pic, int ocw3) {
    outb(pic->cmd_port, ocw3);
    return inb(pic->cmd_port);
}
