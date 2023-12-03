#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

static bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*)data;
    for (size_t i = 0; i < length; i++) {
        if (putchar(bytes[i]) == EOF)
            return false;
    }

    return true;
}

int int_to_string_decimal(char* str, int number) {
    int length = 0;

    if (number < 0) {
        str[length] = '-';
        number = -number;
        length++;
    }

    while (number != 0) {
        int digit = number % 10;
        str[length] = digit + '0';
        number /= 10;
        length++;
    }

    str[length] = '\0';

    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }

    return length;
}

int int_to_string_hex(char* str, int number) {
    int length = 0;

    char hex_digits[16] = "0123456789abcdef";

    while (number != 0) {
        int digit = number % 16;
        str[length] = hex_digits[digit];
        number /= 16;
        length++;
    }

    str[length] = '\0';

    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }

    return length;
}

int printf(const char* format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int written_chars = 0;

    while (format[0] != '\0') {
        if (format[0] != '%') {
            putchar(format[0]);
            written_chars++;
            format++;
        }
        else {
            format++;
            
            if (format[0] == 's') {
                const char* param = (const char*)va_arg(parameters, const char*);
                int length = strlen(param);
                print(param, length);
                written_chars += length;
            }
            else if (format[0] == 'c') {
                char param = (char)va_arg(parameters, int);
                putchar(param);
                written_chars++;
            }
            else if (format[0] == 'd') {
                int param = (int)va_arg(parameters, int);
                char str[7];
                int length = int_to_string_decimal(str, param);
                print(str, length);
                written_chars += length;
            }
            else if (format[0] == 'x') {
                int param = (int)va_arg(parameters, int);
                char str[9];
                int length = int_to_string_hex(str, param);
                print(str, length);
                written_chars += length;
            }
            else {
                putchar('%');
                putchar(format[0]);
                written_chars += 2;
            }

            format++;
        }
    }

    va_end(parameters);
    return written_chars;
}
