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
        } else {
            printf("Title: %s\n", data->title);
            printf("Satellite Number: %d\n", data->sat_num);
            printf("Classifier: %c\n", data->class);
            printf("Launch Year: %s\n", data->launch_yr);
            printf("Launch Number: %d\n", data->launch_num);
            printf("Launch Piece: %s\n", data->launch_piece);
            printf("Epoch Year: %s\n", data->epoch_yr);
            printf("Epoch Day: %f\n", data->epoch_day);
            printf("Derivative of Mean Motion / 2: %f\n", data->d_mean_motion);
            printf("2nd Derivative of Mean Motion / 6: %f\n", data->dd_mean_motion);
            printf("B* Drag Term: %f\n", data->drag);
            printf("Ephemeris Type: %c\n", data->ephemeris);
            printf("Element Number: %d\n", data->element_num);
            printf("Inclination: %f\n", data->inclination);
            printf("Right Node Ascension: %f\n", data->r_node_ascension);
            printf("Eccentricity: %f\n", data->eccentricity);
            printf("Argument of Perigee: %f\n", data->perigee_arg);
            printf("Mean Anomaly: %f\n", data->mean_anomaly);
            printf("Revolutions Per Day: %f\n", data->rev_per_day);
            printf("Revolutions: %d\n", data->rev_num);

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