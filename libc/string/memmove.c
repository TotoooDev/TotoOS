#include <string.h>

void* memmove(void* dest, const void* src, size_t length) {
    unsigned char* dest_ptr = (unsigned char*)dest;
    const unsigned char* src_ptr = (const unsigned char*)src;
    if (dest_ptr < src_ptr) {
        for (size_t i = 0; i < length; i++) {
            dest_ptr[i] = src_ptr[i];
        }
    }
    else {
        for (size_t i = length; i > 0; i--) {
            dest_ptr[i - 1] = src_ptr[i - 1];
        }
    }

    return dest;
}
