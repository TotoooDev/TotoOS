#include <string.h>

void* memset(void* mem, int constant, size_t length) {
    unsigned char* mem_ptr = (unsigned char*)mem;
    for (size_t i = 0; i < length; i++) {
        mem_ptr[i] = (unsigned char)constant;
    }

    return mem;
}
