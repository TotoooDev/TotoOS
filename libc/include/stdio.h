#ifndef _LIBC_STDIO_H
#define _LIBC_STDIO_H

#include <sys/cdefs.h>
#include <stdarg.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int vsprintf(char* str, const char* format, va_list parameters);
int sprintf(char* str, const char* format, ...);
int printf(const char* str, ...);
int putchar(int c);
int puts(const char* str);

#ifdef __cplusplus
}
#endif

#endif
