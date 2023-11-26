#include <string.h>

int memcmp(const void* a, const void* b, size_t length) {
    const unsigned char* a_ptr = (const unsigned char*)a;
    const unsigned char* b_ptr = (const unsigned char*)b;
    for (size_t i = 0; i < length; i++) {
        if (a_ptr[i] < b_ptr[i])
            return -1;
        else if (a_ptr[i] > b_ptr[i])
            return 1;
    }
    
    return 0;
}
