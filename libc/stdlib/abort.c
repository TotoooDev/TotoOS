#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void) {
    #ifdef __is_libk
        // TODO: Add proper kernel panic
        printf("kernel: panic: abort()\n");
        asm volatile("hlt");
    #else
        // TODO: abnormally terminate the program
        printf("abort()\n");
    #endif

    while (1) {}
    __builtin_unreachable();
}
