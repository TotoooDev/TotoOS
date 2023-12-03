#include <kernel/gdt.h>
#include <stdio.h>

void encode_gdt_entry(uint8_t* target, GDT source) {
    // Check the limit to make sure it can be encoded
    if (source.limit > 0xFFFFF) {
        printf("GDT cannot encode limits larger than 0xFFFFF!\n");
        return;
    }

    // Encode the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0xFF;

    // Encode the base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    // Encode the access byte
    target[5] == source.access_byte;

    // Encode the flags
    target[6] |= source.flags << 4;
}
