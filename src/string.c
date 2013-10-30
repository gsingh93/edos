#include "string.h"

void memset(void *obj, uint8_t val, uint32_t size) {
    uint8_t *mem = (uint8_t *) obj;
    for (int i = 0; i < size; i++) {
        mem[i] = val;
    }
}
