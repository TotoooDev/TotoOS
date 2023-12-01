#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#define DELIMITER_MAX_SEARCH 2048

/**
 * Searches for '\0' or '%' characters in str and returns the index of the delimiter.
 * The function returns -1 if the delimiter is not found in a max_search range.
 */
int seek_delimiter(const char* str, int max_search) {
    // kinda dangerous
    for (int index = 0; index < max_search; index++) {
        if (str[index] == '\0' || str[index] == '%')
            return index;
        index++;
    }

    return -1;
}

/**
 * Writes format to str until a delimiter character is found.
 * Returns the number of written bytes.
 */
int write_no_parameter(char* str, const char* format) {
    int next_delimiter = seek_delimiter(format, DELIMITER_MAX_SEARCH);
    memcpy(str, format, next_delimiter);
    return next_delimiter;
}

int int_to_string(int number, char* str) {

}

/**
 * Converts a parameter from format to its string representation and writes it to str.
 * Returns the number of written bytes.
 */
int write_paramater(char* str, const char* format, va_list parameters) {
    switch (format[1]) {
    case 'd':
        break;

    case 'x':
        break;
    }

    return 2;
}

int vsprintf(char* str, const char* format, va_list parameters) {
    int written_chars = 0;

    // Loop through every character of the format string
    while (format[0] != '\0') {
        int written = 0; // the amount of characters written in the current iteration

        if (format[0] != '%') {
            written = write_no_parameter(str, format);
        }
        else {
            written = write_paramater(str, format, parameters);
        }

        written_chars += written;
        format += written;
    }

    return written_chars;
}
