#include <stdio.h>
#include <kernel/terminal.h>

void kernel_main(void) {
    terminal_initialize();
    printf("Welcome to TotoOS!\n");
}