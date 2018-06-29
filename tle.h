#ifndef FATE_TLE_H
#define FATE_TLE_H

typedef char *year;

typedef struct tle_data {
    /* TITLE LINE */
    char *title;
    unsigned char title_len;

    /* LINE 1 */

    int sat_num;
    char class;

    year launch_yr;
    short launch_num;
    char *launch_piece;
    unsigned char launch_piece_len;

    year epoch_yr;
    double epoch_day;

    double d_mean_motion; /* n_0_dot / 2 */
    double dd_mean_motion; /* n_0_dot_dot / 6 */

    double drag;

    unsigned char ephemeris;
    short element_num;
    /* checksum */

    /* LINE 2 */

    double inclination; /* i_0 */
    double r_node_ascension; /* omega_0 */
    double eccentricity; /* e_0 */
    double perigee_arg; /* omega_0 */
    double mean_anomaly; /* M_0 */
    double rev_per_day; /* n_0 */
    int rev_num;
    /* checksum */
} tle_data;

/**
 * Parses and TLE-formatted data using the 3 line format
 * that includes the title line.
 *
 * @param title the title
 * @param line1 the first line
 * @param line2 the second line
 * @return the TLE parsed data, or NULL on failure
 */
tle_data *tle_parse(const char *title, const char *line1, const char *line2);

/**
 * Relinquishes memory allocated to hold the tle_data
 * struct.
 *
 * @param data the data struct to free
 */
void tle_free(tle_data *data);

#endif /* FATE_TLE_H */
