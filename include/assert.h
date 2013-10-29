#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "screen.h"
#include "defs.h"
#include "util_asm.h"

#define ASSERT(cond)                                       \
    do {                                                   \
        if (!cond) {                                       \
            set_text_color(RED, BLACK);                    \
            puts("Assertion '" #cond "' failed at line "); \
            puti(__LINE__);                                \
            puts(" of file " __FILE__);                    \
            asm("hlt");                                    \
        }                                                  \
    } while (0);

#define ASSERT_INTERRUPTS_ENABLED() ASSERT((get_eflags() & (1 << 9)) == 1)
#define ASSERT_INTERRUPTS_DISABLED() ASSERT((get_eflags() & (1 << 9)) == 0)

#endif
