#ifndef _STRING_H_
#define _STRING_H_

#include <stdint.h>

/** Sets size bytes starting at obj to val */
void memset(void *obj, uint8_t val, uint32_t size);

/** Returns the length of str, not including null byte */
uint32_t strlen(const char *str);

#endif
