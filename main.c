#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tle.h"
#include "sgp.h"
#include "astrotime.h"
#include "eci.h"

int main(int argc, char **argv) {
    static const int line_cnt = 3;

    char **lines = calloc(line_cnt, sizeof(*lines));
    long *line_size = calloc(line_cnt, sizeof(*line_size));
    while (1) {
        puts("Enter 3LE Data:");
        line_size[0] = getline(&lines[0], (size_t *) &line_size[0], stdin);
        if (strcmp(lines[0], "exit\n") == 0) {
            break;
        }

        line_size[1] = getline(&lines[1], (size_t *) &line_size[1], stdin);
        if (strcmp(lines[1], "exit\n") == 0) {
            break;
        }

        line_size[2] = getline(&lines[2], (size_t *) &line_size[2], stdin);
        if (strcmp(lines[2], "exit\n") == 0) {
            break;
        }

        tle_data *data = tle_parse(lines[0], lines[1], lines[2]);
        if (data == NULL) {
            puts("Error occurred parsing data");
        } else {
            jd target = to_jd(2018, 8, 16, 8, 44, 40);
            lat_lon observer = { 47, -122 };
            look_result look = eci_to_look(data, observer, target);
            lat_lon sub_point = eci_to_lat_lon(data, target);

            printf("Look: %f %f\n", look.azimuth, look.altitude);
            printf("Pos: %f, %f\n", sub_point.lat, sub_point.lon);

            tle_free(data);
        }

        puts("");
    }

    for (int i = 0; i < line_cnt; ++i) {
        free(lines[i]);
    }
    free(lines);
    free(line_size);
}