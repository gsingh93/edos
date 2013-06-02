#ifndef _IDT_H_
#define _IDT_H_

#include "isr.h"
#include <stdint.h>

void init_idt(void);
void idt_create_descriptor(uint8_t i, isr_function isr_fn, uint8_t type);

#endif
