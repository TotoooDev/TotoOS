#ifndef _LIBC_STRING_H
#define _LIBC_STRING_H

#include <stddef.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

int memcmp(const void* a, const void* b, size_t length);
void* memcpy(void* __restrict dest, const void* __restrict src, size_t length);
void* memmove(void* dest, const void* src, size_t length);
void* memset(void* mem, int constant, size_t length);
size_t strlen(const char* str);

#ifdef __cplusplus
}
#endif

#endif
