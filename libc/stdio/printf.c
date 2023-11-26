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

int printf(const char* __restrict formatted_str, ...) {
    va_list parameters;
    va_start(parameters, formatted_str);

    int written = 0;

    while (*formatted_str != '\0') {
        size_t maxrem = INT_MAX - written;

        if (formatted_str[0] != '%' || formatted_str[1] == '%') {
            if (formatted_str[0] == '%')
                formatted_str++;

            size_t amount = 1;
            while (formatted_str[amount] && formatted_str[amount] != '%')
                amount++;

            if (amount > maxrem)
                return -1;

            if (!print(formatted_str, amount))
                return -1;

            formatted_str += amount;
            written += amount;
            continue;
        }
        
        const char* format_begun_at = formatted_str;
        formatted_str++;

        if (*formatted_str == 'c') {
            formatted_str++;
            char c = (char)va_arg(parameters, int); // char promotes to int

            if (!maxrem)
                return -1;

            if (!printf(&c, sizeof(c)))
                return -1;

            written++;
        }
        else if (*formatted_str == 's') {
            formatted_str++;
            const char* str = (const char*)va_arg(parameters, const char*);
            size_t len = strlen(str);

            if (!maxrem)
                return -1;

            if (!printf(str, len))
                return -1;

            written += len;
        }
        else {
            formatted_str = format_begun_at;
			size_t len = strlen(formatted_str);

			if (maxrem < len)
				return -1;

			if (!print(formatted_str, len))
				return -1;
			
            written += len;
			formatted_str += len;
        }
    }

    va_end(parameters);
    return written;
}
