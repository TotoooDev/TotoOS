#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <stdint.h>

typedef struct GDT {
    uint32_t base;
    uint16_t limit;
    uint8_t access_byte;
    uint8_t flags;
} GDT;

void encode_gdt_entry(uint8_t* target, GDT source);

#endif
