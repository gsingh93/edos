#ifndef _IDT_H_
#define _IDT_H_

#include <stdint.h>

/*
 * A stack frame when an ISR is called
 */
typedef struct {
    uint32_t gs, fs, es, ds; // These are the last things pushed to the stack
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt_number, error_code;
    uint32_t eip, cs, eflags, useresp, ss;
} interrupt_stack_frame_t;

typedef void (idt_function)(void);
typedef void (interrupt_handler)(interrupt_stack_frame_t);

extern interrupt_handler *interrupt_handlers[256];

void init_idt(void);
void idt_create_descriptor(uint8_t index, idt_function *idt_fn, uint8_t type);
void register_interrupt_handler(uint8_t index, interrupt_handler *handler);

#endif
