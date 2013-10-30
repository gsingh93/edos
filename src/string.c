#include "string.h"

void memset(void *obj, uint8_t val, uint32_t size) {
    uint8_t *mem = (uint8_t *) obj;
    for (int i = 0; i < size; i++) {
        mem[i] = val;
    }
}

uint32_t strlen(const char *str) {
    uint32_t len = 0;
    while (*str++) {
        len++;
    }
    return len;
}
