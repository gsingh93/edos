#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stdint.h>

/** Allocate virtual memory */
uint32_t kmalloc(uint32_t size);

/** Allocate page aligned virtual memory */
uint32_t kmalloc_a(uint32_t size);

#endif
