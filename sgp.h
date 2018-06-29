#include "tle.h"
#include "util.h" /* TODO: Remove include */

#ifndef FATE_SGP_H
#define FATE_SGP_H

const double G = WORK_NEEDED_ARG; /* TODO: Gravitational constant */
const double MASS_OF_EARTH = WORK_NEEDED_ARG; /* TODO: Mass of earth */
const double S = WORK_NEEDED_ARG; /* TODO: SGP density func */
const double Q_0 = WORK_NEEDED_ARG;
const double XKMPER = 6378.135;
const double J_3 = -.253881E-5;
const double A_3_COMMA_0 = -J_3 * 6379.137 * 6379.137 * 6379.137; /* -J_3 * cube(earth_radius(0)) */

typedef struct sgp_data {
} sgp_data;

sgp_data *sgp4(tle_data *data);

#endif /* FATE_SGP_H */
