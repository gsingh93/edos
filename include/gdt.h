#ifndef _GDT_H_
#define _GDT_H_

#include <stdint.h>

/** Initialize the GDT structure and set the GDTR register */
void init_gdt(void);

#endif
