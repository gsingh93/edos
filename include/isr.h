#ifndef _ISR_H_
#define _ISR_H_

typedef void (*isr_function)(void);

void init_isrs(void);

#endif
