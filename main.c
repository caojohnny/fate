#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tle.h"

int main(int argc, char **argv) {
    static const int line_cnt = 3;

    char **lines = calloc(line_cnt, sizeof(*lines));
    long *line_size = calloc(line_cnt, sizeof(*line_size));
    while (1) {
        puts("Enter 3LE Data:");
        line_size[0] = getline(&lines[0], &line_size[0], stdin);
        if (strcmp(lines[0], "exit\n") == 0) {
            break;
        }

        line_size[1] = getline(&lines[1], &line_size[1], stdin);
        if (strcmp(lines[1], "exit\n") == 0) {
            break;
        }

        line_size[2] = getline(&lines[2], &line_size[2], stdin);
        if (strcmp(lines[2], "exit\n") == 0) {
            break;
        }

        tle_data *data = tle_parse(lines[0], lines[1], lines[2]);
        if (data == NULL) {
            puts("Error occurred parsing data");
            continue;
        }

        printf("Title: %s\n", data->title);
        printf("Satellite Number: %d\n", data->sat_num);
        printf("Classifier: %c\n", data->class);

        tle_free(data);

        puts("");
    }

    for (int i = 0; i < line_cnt; ++i) {
        free(lines[i]);
    }
    free(lines);
    free(line_size);
}