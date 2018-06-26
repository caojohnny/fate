#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "tle.h"
#include "util.h"

static tle_data *new_tle_data() {
    tle_data *data = calloc(1, sizeof(*data));
    return data;
}

/**
 * Designed to parse space-track.org title lines, they are
 * prefixed with "0 " so the max len would be 26 and not 24
 *
 * @param data the data to fill
 * @param title the title line
 * @return 0 if invalid length
 */
static int parse_title(tle_data *data, char *title) {
    size_t len = strlen(title);
    if (len > 26) {
        return 0;
    }

    /*  Cut the beginning "0 " and the newline */
    len -= 3;

    data->title_len = len;
    data->title = substr(title, 2, len);
    if (data->title == NULL) {
        return 0;
    }

    return 1;
}

static int parse_line1(tle_data *data, char *line1) {
    /* sat_num */
    char *sat_num_str = substr(line1, 2, 5);
    if (sat_num_str == NULL) {
        return 0;
    }

    if (strl(sat_num_str, &data->sat_num) == 0) {
        return 0;
    }

    free(sat_num_str);

    /* class */
    data->class = line1[7];

    /* launch_yr */
    data->launch_yr = substr(line1, 9, 2);
    if (data->launch_yr == NULL) {
        return 0;
    }

    /* launch_num */
    char *launch_num_str = substr(line1, 11, 3);
    if (launch_num_str == NULL) {
        return 0;
    }

    if (strl(launch_num_str, &data->launch_num) == 0) {
        return 0;
    }

    free(launch_num_str);

    /* launch_piece */
    data->launch_piece = substr(line1, 14, 3);
    if (data->launch_piece == NULL) {
        return 0;
    }
    data->launch_piece_len = strlen(data->launch_piece);

    /* epoch_yr */
    data->epoch_yr = substr(line1, 18, 2);
    if (data->epoch_yr == NULL) {
        return 0;
    }

    /* epoch_day */
    char *epoch_day_str = substr(line1, 20, 12);
    if (epoch_day_str == NULL) {
        return 0;
    }

    if (strd(epoch_day_str, &data->epoch_day) == 0) {
        return 0;
    }

    free(epoch_day_str);

    /* d_mean_motion */
    char *d_mean_motion_str = substr(line1, 33, 10);
    if (d_mean_motion_str == NULL) {
        return 0;
    }

    if (strd(d_mean_motion_str, &data->d_mean_motion) == 0) {
        return 0;
    }

    free(d_mean_motion_str);

    /* dd_mean_motion */



    return 1;
}

static int parse_line2(tle_data *data, char *line2) {
    return 1;
}

tle_data *tle_parse(char *title, char *line1, char *line2) {
    tle_data *data = new_tle_data();
    if (parse_title(data, title) == 0) {
        return NULL;
    }

    if (parse_line1(data, line1) == 0) {
        return NULL;
    }

    if (parse_line2(data, line2) == 0) {
        return NULL;
    }

    return data;
}

void tle_free(tle_data *data) {
    free(data->title);
    free(data->launch_yr);
    free(data->launch_piece);
    free(data->epoch_yr);
    free(data);
}