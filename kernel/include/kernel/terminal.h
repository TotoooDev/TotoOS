#ifndef _KERNEL_TERMINAL_H
#define _KERNEL_TERMINAL_H

#include <stddef.h>

void terminal_initialize(void);
void terminal_put_char(char entry);
void terminal_write(const char* data, size_t size);
void terminal_write_string(const char* str);

#endif
