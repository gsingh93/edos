#ifndef _UTIL_ASM_H_
#define _UTIL_ASM_H_

/** Returns the value of the EFLAGS register */
uint32_t get_eflags();

/** Disables interrupts */
void clear_interrupts();

/** Enables interrupts */
void set_interrupts();

#endif
