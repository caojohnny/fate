#include <stdlib.h>
#include <memory.h>
#include "util.h"

double square(double);

double cube(double);

double to_radians(double);

double frac(double);

char *substr(const char *str, int start, int len) {
    char *substr = malloc(len + 1);
    if (substr == NULL) {
        return NULL;
    }

    memcpy(substr, str + start, len);
    substr[len] = '\0';

    return substr;
}

int strl(const char *str, long *value) {
    char *end_ptr = NULL;
    long result = strtol(str, &end_ptr, 10);
    if (result == 0 && str == end_ptr) {
        return 0;
    }

    *value = result;
    return 1;
}

int strd(const char *str, double *value) {
    char *end_ptr = NULL;
    double result = strtod(str, &end_ptr);
    if (result == 0 && str == end_ptr) {
        return 0;
    }

    *value = result;
    return 1;
}
