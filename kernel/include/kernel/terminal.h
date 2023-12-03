#ifndef _KERNEL_TERMINAL_H
#define _KERNEL_TERMINAL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

void terminal_initialize(void);
void terminal_put_char(char entry);
void terminal_write(const char* data, size_t size);
void terminal_write_string(const char* str);
void terminal_clear(char c);
// UNSTABLE
void terminal_set_attributes(uint8_t foreground, uint8_t background, bool blink, bool underlined);

#endif
