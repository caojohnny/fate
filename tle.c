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

// TODO: I have no clue lol
static int compute_checksum(char *str) {
    int len = strlen(str);
    int total = 0;
    for (int i = 2; i < len; i++) {
        char c = str[i];
        if (c == '-') {
            total += 1;
        } else if (c >= '0' && c <= '9') {
            total += c - '0';
        }
    }

    return total % 10;
}

static int parse_line1(tle_data *data, char *line1) {
    int checksum = line1[68] - '0';
    if (compute_checksum(line1) != checksum) {
        puts("Checksum failed");
        return 0;
    }

    /* sat_num */
    char *sat_num_str = substr(line1, 2, 5);
    if (sat_num_str == NULL) {
        return 0;
    }

    if (strl(sat_num_str, &data->sat_num) == 0) {
        free(sat_num_str);
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
        free(launch_num_str);
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
        free(epoch_day_str);
        return 0;
    }

    free(epoch_day_str);

    /* d_mean_motion */
    char *d_mean_motion_str = substr(line1, 33, 10);
    if (d_mean_motion_str == NULL) {
        return 0;
    }

    if (strd(d_mean_motion_str, &data->d_mean_motion) == 0) {
        free(d_mean_motion_str);
        return 0;
    }

    free(d_mean_motion_str);

    /* dd_mean_motion */
    double dd_mean_motion_mul = 0;
    char *dd_mean_motion_mul_str = substr(line1, 44, 6);
    if (dd_mean_motion_mul_str == NULL) {
        return 0;
    }

    if (strd(dd_mean_motion_mul_str, &dd_mean_motion_mul) == 0) {
        free(dd_mean_motion_mul_str);
        return 0;
    }

    free(dd_mean_motion_mul_str);
    dd_mean_motion_mul /= 100000;

    int dd_mean_motion_exp = 0;
    char *dd_mean_motion_exp_str = substr(line1, 50, 2);
    if (dd_mean_motion_exp_str == NULL) {
        return 0;
    }

    if (strl(dd_mean_motion_exp_str, &dd_mean_motion_exp) == 0) {
        free(dd_mean_motion_exp_str);
        return 0;
    }

    free(dd_mean_motion_exp_str);
    data->dd_mean_motion = dd_mean_motion_mul * pow(10, dd_mean_motion_exp);

    /* drag */
    double drag_mul = 0;
    char *drag_mul_str = substr(line1, 53, 6);
    if (drag_mul_str == NULL) {
        return 0;
    }

    if (strd(drag_mul_str, &drag_mul) == 0) {
        free(drag_mul_str);
        return 0;
    }

    free(drag_mul_str);
    drag_mul /= 100000;

    int drag_exp = 0;
    char *drag_exp_str = substr(line1, 59, 2);
    if (drag_exp_str == NULL) {
        return 0;
    }

    if (strl(drag_exp_str, &drag_exp) == 0) {
        free(drag_exp_str);
        return 0;
    }

    free(drag_exp_str);
    data->drag = drag_mul * pow(10, drag_exp);

    /* ephemeris */
    data->ephemeris = line1[62];

    /* element_num */
    char *element_num_str = substr(line1, 64, 4);
    if (element_num_str == NULL) {
        return 0;
    }

    if (strl(element_num_str, &data->element_num) == 0) {
        free(element_num_str);
        return 0;
    }

    free(element_num_str);

    return 1;
}

static int parse_line2(tle_data *data, char *line2) {
    int checksum = line2[68] - '0';
    if (compute_checksum(line2) != checksum) {
        puts("Checksum failed");
        return 0;
    }

    /* ignore satellite number */

    /* inclination */
    char *inclination_str = substr(line2, 8, 8);
    if (inclination_str == NULL) {
        return 0;
    }

    if (strd(inclination_str, &data->inclination) == 0) {
        free(inclination_str);
        return 0;
    }

    free(inclination_str);

    /* r_node_ascension */
    char *r_node_ascension_str = substr(line2, 17, 8);
    if (r_node_ascension_str == NULL) {
        return 0;
    }

    if (strd(r_node_ascension_str, &data->r_node_ascension) == 0) {
        free(r_node_ascension_str);
        return 0;
    }

    free(r_node_ascension_str);

    /* eccentricity */
    double eccentricity = 0;
    char *eccentricity_str = substr(line2, 26, 7);
    if (eccentricity_str == NULL) {
        return 0;
    }

    if (strd(eccentricity_str, &eccentricity) == 0) {
        free(eccentricity_str);
        return 0;
    }

    free(eccentricity_str);
    data->eccentricity = eccentricity /= 10000000;

    /* perigee_arg */
    char *perigee_arg_str = substr(line2, 34, 8);
    if (perigee_arg_str == NULL) {
        return 0;
    }

    if (strd(perigee_arg_str, &data->perigee_arg) == 0) {
        free(perigee_arg_str);
        return 0;
    }

    free(perigee_arg_str);

    /* mean_anomaly */
    char *mean_anomaly_str = substr(line2, 43, 8);
    if (mean_anomaly_str == NULL) {
        return 0;
    }

    if (strd(mean_anomaly_str, &data->mean_anomaly) == 0) {
        free(mean_anomaly_str);
        return 0;
    }

    free(mean_anomaly_str);

    /* rev_per_day */
    char *rev_per_day_str = substr(line2, 52, 11);
    if (rev_per_day_str == NULL) {
        return 0;
    }

    if (strd(rev_per_day_str, &data->rev_per_day) == 0) {
        free(rev_per_day_str);
        return 0;
    }

    free(rev_per_day_str);

    /* rev_num */
    char *rev_num_str = substr(line2, 63, 5);
    if (rev_num_str == NULL) {
        return 0;
    }

    if (strl(rev_num_str, &data->rev_num) == 0) {
        free(rev_num_str);
        return 0;
    }

    free(rev_num_str);

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