#ifndef _PORTIO_H_
#define _PORTIO_H_

#include <stdint.h>

/** Writes a byte to the specified port */
void outb(uint16_t port, uint8_t byte);

/** Reads a byte from the specified port */
uint8_t inb(uint16_t port);

#endif
