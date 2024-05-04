// mostly stolen from https://wiki.osdev.org/Bare_Bones

/*
welcome to the high-level world of c!
we have:
    - no standard library
    - no dynamic memory allocation (for now)
*/

// we don't have access to the standard library, but the compiler gives us some handy headers
#include <stddef.h>
#include <stdint.h>

// you really should be using a cross-compiler
#if defined(__linux__)
    #warning "you are not using a cross-compiler! here be dragons!"
#endif

#if !defined(__i386__)
    #error "this code should be compiled with a ix86-elf compiler"
#endif

// define a very simple vga driver

// define some constants
#define VGA_ADDRESS 0xb8000
#define VGA_WIDTH   80
#define VGA_HEIGHT  25

// terminal data
static size_t terminal_current_row;
static size_t terminal_current_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer; 

typedef enum VGAColor {
    VGA_COLOR_BLACK         = 0,
    VGA_COLOR_BLUE          = 1,
    VGA_COLOR_GREEN         = 2,
    VGA_COLOR_CYAN          = 3,
    VGA_COLOR_RED           = 4,
    VGA_COLOR_MAGENTA       = 5,
    VGA_COLOR_BROWN         = 6,
    VGA_COLOR_LIGHT_GREY    = 7,
    VGA_COLOR_DARK_GREY     = 8,
    VGA_COLOR_LIGHT_BLUE    = 9,
    VGA_COLOR_LIGHT_GREEN   = 10,
    VGA_COLOR_LIGHT_CYAN    = 11,
    VGA_COLOR_LIGHT_RED     = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN   = 14,
    VGA_COLOR_WHITE         = 15
} VGAColor;

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

// here static inline is used to indicate to the compiler to not use a call mechanism with the function.
// this is used when dealing with small and simple functions.
static inline uint8_t vga_get_entry_color(VGAColor foreground, VGAColor background) {
    return foreground | background << 4;
}

static inline uint16_t vga_get_entry(unsigned char entry, uint8_t color) {
    return (uint16_t)entry | (uint16_t)color << 8;
}

void terminal_initialize(void) {
    terminal_current_row = 0;
    terminal_current_column = 0;
    terminal_color = vga_get_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*)VGA_ADDRESS;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_get_entry(' ', terminal_color);
        }
    }
}

void terminal_newline(void) {
    terminal_current_column = 0;
    terminal_current_row++;

    if (terminal_current_row >= VGA_HEIGHT) {
        terminal_current_row = 0;
    }
}

void terminal_set_color(uint8_t color) {
    terminal_color = color;
}

void terminal_put_char_at(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_get_entry(c, color);
}

void terminal_put_char(char c) {
    terminal_put_char_at(c, terminal_color, terminal_current_column, terminal_current_row);
    terminal_current_column++;

    // reset the cursor position if we hit the end of a line or the end of the screen
    if (terminal_current_column >= VGA_WIDTH) {
        terminal_newline();
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_put_char(data[i]);
    }
}

void terminal_write_string(const char* str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (str[i] == '\n') {
            terminal_newline();
            continue;
        }

        terminal_put_char(str[i]);
    }
}

void terminal_print(const char* str) {
    terminal_write_string(str, strlen(str));
}

// entrypoint of our super duper kernel!
void kernel_main(void) {
    terminal_initialize();
    terminal_print("Hello world!\n");
    terminal_print("now with newline support!\n");
    terminal_print("so cool\n");
    terminal_print("just don't go too far down...\n");
}
