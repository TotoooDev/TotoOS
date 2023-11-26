#ifndef _LIBC_STDIO_H
#define _LIBC_STDIO_H

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict formatted_str, ...);
int putchar(int c);
int puts(const char* str);

#ifdef __cplusplus
}
#endif

#endif
