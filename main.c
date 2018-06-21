#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "earth.h"

int main() {
    char *line = NULL;
    while (1) {
        printf("Latitude: ");

        size_t line_size = 0;
        getline(&line, &line_size, stdin);

        char *endptr = NULL;
        double in = strtod(line, &endptr);
        if (*line == *endptr || *endptr != '\n') {
            if (strcmp(line, "exit\n") == 0) {
                free(line);
                return 0;
            } else {
                printf("Not a number: %s\n", line);
                continue;
            }
        }

        printf("Radius at %f deg is %f km\n\n", in, earth_radius(in));
    }
}