#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/terminal.h>

#include "vga.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY_LOCATION 0xB8000

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

size_t terminal_get_index(size_t x, size_t y) {
    return y * VGA_WIDTH + x;
}

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*)VGA_MEMORY_LOCATION;
    
    terminal_clear('\0');
}

void terminal_set_color(uint8_t color) {
    terminal_color = color;
}

void terminal_put_entry_at(unsigned char entry, uint8_t color, size_t x, size_t y) {
    const size_t index = terminal_get_index(x, y);
    terminal_buffer[index] = vga_entry(entry, color);
}

void terminal_scroll() {
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        memmove(terminal_buffer + ((y - 1) * VGA_WIDTH), terminal_buffer + (y * VGA_WIDTH), VGA_WIDTH);
    }
    memset(terminal_buffer + ((VGA_HEIGHT - 1) * VGA_WIDTH), '\0', VGA_WIDTH);
    terminal_row--;
}

void terminal_new_line() {
    terminal_column = 0;
    terminal_row++;
    if (terminal_row >= VGA_HEIGHT) {
        terminal_scroll();
    }
}

void terminal_put_char(char entry) {
    if (entry == '\n') {
        terminal_new_line();
        return;
    }

    unsigned char uc = entry;
    terminal_put_entry_at(uc, terminal_color, terminal_column, terminal_row);
    
    terminal_column++;
    if (terminal_column >= VGA_WIDTH) {
        terminal_new_line();
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_put_char(data[i]);
}

void terminal_write_string(const char* str) {
    terminal_write(str, strlen(str));
}

void terminal_clear(char c) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = terminal_get_index(x, y);
            terminal_buffer[index] = vga_entry(c, terminal_color);
        }
    }
}

// UNSTABLE
// TODO: Finish this function to enable blinking and underlined text
void terminal_set_attributes(uint8_t foreground, uint8_t background, bool blink, bool underlined) {
    uint8_t blink_bit = (uint8_t)blink << 7;
    uint8_t background_color = (background & 0b00000111) << 4;
    uint8_t foreground_color = foreground;
    terminal_color = blink_bit | background_color | foreground_color;

    if (underlined) {
        uint8_t underline_mask = 0b10001001;
        terminal_color &= underline_mask;
    }
}
