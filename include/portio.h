#ifndef _PORTIO_H_
#define _PORTIO_H_

#include <stdint.h>

void outb(uint16_t port, uint8_t byte);
uint8_t inb(uint16_t port);

#endif
