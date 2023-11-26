#include <stdio.h>

#include <kernel/terminal.h>

void kernel_main(void) {
    terminal_initialize();
    for (size_t i = 0; i < 25; i++)
        printf("Welcome to TotoOS!\n");
    printf("This is the best kernel ever.\n");
    printf("Now with terminal scrolling!\n");
    printf("So cool.\n");
}