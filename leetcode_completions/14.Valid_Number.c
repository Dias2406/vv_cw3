#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

bool isNumber(char* s) {
    if (!s || *s == '\0') return false;

    char* p = s;

    while (*p == ' ') p++;  // Skip leading whitespaces

    if (*p == '+' || *p == '-') p++;  // Check for optional sign

    bool hasDigits = false, hasDot = false, hasExponent = false;

    while (isdigit(*p) || *p == '.') {
        if (*p == '.') {
            if (hasDot || hasExponent) return false;
            hasDot = true;
        } else {
            hasDigits = true;
        }
        p++;
    }

    if (hasDot && *(p-1) == '.' && !isdigit(*(p-2)) && !isdigit(*p)) return false;

    if (*p == 'e' || *p == 'E') {
        if (!hasDigits) return false;
        hasExponent = true;
        p++;
        if (*p == '+' || *p == '-') p++;
        if (!isdigit(*p)) return false;
        while (isdigit(*p)) p++;
    }

    while (*p == ' ') p++;  // Skip trailing whitespaces

    return *p == '\0' && hasDigits;
}