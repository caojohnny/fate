#include "tle.h"

#ifndef FATE_SGP_H
#define FATE_SGP_H

typedef struct vec {
    double x;
    double y;
    double z;
} vec;

typedef struct sgp_data {
    vec u; /* orientation */
    vec v;

    vec r; /* position */
    vec r_dot; /* velocity */
} sgp_result;

sgp_result sgp4(tle_data *data, long minutes_since_epoch);

#endif /* FATE_SGP_H */
