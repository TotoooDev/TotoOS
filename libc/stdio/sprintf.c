#include <stdio.h>
#include <stdarg.h>

int sprintf(char* str, const char* format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int written_chars = 0;

    // Loop through every character of the foramt string
    while (format[0] != '\0') {
        if (format[0] == '%') {
            
        }
        else {

        }
    }

    va_end(parameters);
    return written_chars;
}
