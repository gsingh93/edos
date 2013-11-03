#ifndef _PIC_H_
#define _PIC_H_

#include <stdint.h>

#define ICW1_ICW4       0x01        /* ICW4 needed                 */
#define ICW1_SINGLE     0x02        /* Single (cascade) mode       */
#define ICW1_INTERVAL4  0x04        /* Call address interval 4 (8) */
#define ICW1_LEVEL      0x08        /* Level triggered (edge) mode */
#define ICW1_INIT       0x10        /* Initialization              */

#define ICW4_8086       0x01        /* 8086/88 (MCS-80/85) mode    */
#define ICW4_AUTO       0x02        /* Auto (normal) EOI           */
#define ICW4_BUF_SLAVE  0x08        /* Buffered mode/slave         */
#define ICW4_BUF_MASTER 0x0C        /* Buffered mode/master        */
#define ICW4_SFNM       0x10        /* Special fully nested (not)  */

typedef struct pic_t {
    uint8_t cmd_port;
    uint8_t data_port;
} pic_t;

typedef enum pic_type_t {
    MASTER, SLAVE
} pic_type_t;

/** Send the PIC the initialization control word */
void PIC_init(pic_t *pic, pic_type_t type);

/** Send the PIC a command */
void PIC_send_command(pic_t* pic, uint8_t command);

/** Send the PIC some data */
void PIC_send_data(pic_t* pic, uint8_t data);

/** Get the value of the IRR register */
uint8_t PIC_get_irr(pic_t *pic);

/** Get the value of the ISR register */
uint8_t PIC_get_isr(pic_t *pic);

#endif
