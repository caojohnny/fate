#ifndef FATE_TLE_H
#define FATE_TLE_H

typedef struct tle_data {
    /* TITLE LINE */
    char *title;
    unsigned char title_len;

    /* LINE 1 */

    int sat_num;
    char class;

    unsigned char launch_yr;
    short launch_num;
    char *launch_piece;
    unsigned char launch_piece_len;

    unsigned char epoch_yr;
    double epoch_day;

    double d_mean_motion;
    double dd_mean_motion;

    double drag;

    /* ephemeris_type (0) */
    short element_num;
    /* checksum */

    /* LINE 2 */

    double inclination;
    double node_ascension;
    double eccentricity;
    double perigee_arg;
    double mean_anomaly;
    double rev_per_day; /* mean_motion */
    int rev_num;
    /* checksum */
} tle_data;

tle_data *parse_3le(char *title, char *line1, char *line2);

#endif /* FATE_TLE_H */
