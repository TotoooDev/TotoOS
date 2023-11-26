#include <string.h>

void* memcpy(void* __restrict dest, const void* __restrict src, size_t length) {
    unsigned char* dest_ptr = (unsigned char*)dest;
    unsigned char* src_ptr = (unsigned char*)src;
    for (size_t i = 0; i < length; i++) {
        dest_ptr[i] = src_ptr[i];
    }
    
    return dest;
}
