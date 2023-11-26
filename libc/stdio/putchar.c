#include <stdio.h>

#ifdef __is_libk
    #include <kernel/terminal.h>
#endif

int putchar(int c) {
    #ifdef __is_libk
        char entry = (char)c;
        terminal_write(&entry, sizeof(char));
    #else
        // TODO: Implement stdio and the write system call
    #endif

    return c;
}
