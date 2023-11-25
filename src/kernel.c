#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Check if the compiler is targeting the wrong operating system.
#ifdef __linux__
    #error "You are not using a cross-compiler! Things will break!"
#endif

// This (tutorial) kernel will only work for the 32-bit ix86-elf systems
#ifndef __i386__
    #error "This kernel needs to be compiled with a ix86-elf compiler."
#endif

// Location of the VGA text mode buffer.
#define VGA_TEXT_MODE_BUFFER_LOCATION 0xB8000

/**
 * Hardware text mode color constants.
 */
typedef enum {
    VGA_COLOR_BLACK         = 0,
    VGA_COLOR_BLUE          = 1,
    VGA_COLOR_GREEN         = 2,
    VGA_COLOR_CYAN          = 3,
    VGA_COLOR_RED           = 4,
    VGA_COLOR_MAGENTA       = 5,
    VGA_COLOR_BROWN         = 6,
    VGA_COLOR_LIGHT_GRAY    = 7,
    VGA_COLOR_DARK_GRAY     = 8,
    VGA_COLOR_LIGHT_BLUE    = 9,
    VGA_COLOR_LIGHT_GREEN   = 10,
    VGA_COLOR_LIGHT_CYAN    = 11,
    VGA_COLOR_LIGHT_RED     = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN   = 14,
    VGA_COLOR_WHITE         = 15
} ColorVGA;

static inline uint8_t vga_entry_color(ColorVGA foreground, ColorVGA background) {
    return foreground | background << 4;
}

static inline uint16_t vga_entry(unsigned char entry, uint8_t color) {
    return (uint16_t)entry | (uint16_t)color << 8;
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize() {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*)VGA_TEXT_MODE_BUFFER_LOCATION;

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; y < VGA_WIDTH; y++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_set_color(uint8_t color) {
    terminal_color = color;
}

void terminal_put_entry_at(char entry, uint8_t color, size_t x, size_t y) {
    const size_t index= y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(entry, color);
}

void terminal_put_char(char entry) {
    terminal_put_entry_at(entry, terminal_color, terminal_column, terminal_row);

    terminal_column++;
    if (terminal_column >= VGA_WIDTH) {
        terminal_column = 0;
        terminal_row++;

        if (terminal_row >= VGA_HEIGHT) {
            terminal_row = 0;
        }
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_put_char(data[i]);
}

void terminal_write_string(const char* str) {
    terminal_write(str, strlen(str));
}

void kernel_main() {
    terminal_initialize();
    terminal_write_string("Hello kernel!\n");
}
