
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lie_detector.h"

void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n && s[n - 1] == '\n')
        s[n - 1] = '\0';
}

void str_tolower(char *s) {
    for (; *s; ++s)
        *s = (char)tolower((unsigned char)*s);
}

int ci_equal(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return 0;
        a++;
        b++;
    }
    return *a == *b;
}
