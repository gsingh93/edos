#ifndef _PIT_H_
#define _PIT_H_

#include <stdint.h>

/** Initializes the PIT with a tick frequency in Hz */
void init_timer(uint32_t frequency);

#endif
