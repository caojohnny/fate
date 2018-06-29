#include <stdlib.h>
#include <math.h>
#include "sgp.h"
#include "util.h"
#include "earth.h"

static sgp_data *new_sgp_data() {
    sgp_data *data = malloc(sizeof(*data));
    return data;
}

sgp_data *sgp4(tle_data *data) {
    sgp_data *result = new_sgp_data();
    if (result == NULL) {
        return NULL;
    }

    double ONE_HALF = 1.0 / 2.0;
    double THREE_HALVES = 3.0 / 2.0;
    double TWO_THIRDS = 2.0 / 3.0;

    double J_2 = WORK_NEEDED_ARG; /* TODO: 2nd gravitational harmonic */
    double a_E = earth_radius(0); /* TODO: Const */

    double k_e = sqrt(G * MASS_OF_EARTH); /* TODO: Const */
    double k_2 = ONE_HALF * J_2 * square(a_E); /* TODO: Const */
    double delta_multiplier = ((3 * square(cos(data->inclination)) - 1) /
                               pow(1 - square(data->eccentricity), THREE_HALVES));

    double a_1 = pow(k_e / data->rev_per_day, TWO_THIRDS);
    double delta_1 = THREE_HALVES * (k_2 / square(a_1)) * delta_multiplier;
    double a_0 = a_1 * (1 - ((1.0 / 3.0) * delta_1) - square(delta_1) - ((134.0 / 81.0) * cube(delta_1)));
    double delta_0 = THREE_HALVES * (k_2 / square(a_0)) * delta_multiplier;
    double d_d_n_0 = data->rev_per_day / (1 + delta_0); /* original mean motion */
    double d_d_a_0 = a_0 / (1 - delta_0); /* semimajor axis */

    double perigee = WORK_NEEDED_ARG;
    double s = S; /* TODO: Const */
    double q_0_minus_s_pow_4 = pow(Q_0 - S, 4); /* TODO: Const */
    if (perigee >= 98 && perigee <= 156) {
        s = (d_d_a_0 * (1 - data->eccentricity)) - S + a_E; /* s_star */
        q_0_minus_s_pow_4 = pow(Q_0 - s, 4); /* TODO: Verify correctness */
    } else if (perigee < 98) {
        s = 20.0 / XKMPER + a_E; /* s_star */
        q_0_minus_s_pow_4 = pow(Q_0 - s, 4); /* TODO: Verify correctness */
    }

    double theta = cos(data->inclination);
    double epsilon = 1 / (d_d_a_0 - s); /* TODO: Verify letter */
    double beta_0 = sqrt(1 - square(data->eccentricity));
    double n = d_d_a_0 * data->eccentricity * epsilon; /* TODO: Verify letter */
    double C_2 =
            q_0_minus_s_pow_4 * pow(epsilon, 4) * d_d_n_0 * pow(1 - square(n), -7.0 / 2.0) * /* TODO: Power function */
            ((d_d_a_0 * (1 + THREE_HALVES * square(n) + 4 * data->eccentricity * n + data->eccentricity * cube(n))) +
             (THREE_HALVES * (k_2 * epsilon) / (1 - square(n))) *
             (-ONE_HALF + THREE_HALVES * square(theta)) *
             (8 + 24 * square(n) + 3 * pow(n, 4)));
    double C_1 = data->drag * C_2;
    double C_3 = (q_0_minus_s_pow_4 * pow(epsilon, 5) * A_3_COMMA_0 * d_d_n_0 * a_E * sin(data->inclination)) /
                 (k_2 / data->eccentricity);
    double C_4 = 2 * d_d_n_0 * q_0_minus_s_pow_4 * pow(epsilon, 4) * d_d_a_0 * square(beta_0) * pow(1 - square(n), -7.0 / 2) *
                 ((2 * n * (1 + data->eccentricity * n) + ONE_HALF * data->eccentricity + ONE_HALF * cube(n)) -
                  ((2 * k_2 * epsilon) / d_d_a_0 * (1 - square(n))) *
                  (
                          3 * (1 - 3 * square(theta)) *
                          (1 + THREE_HALVES * square(n) - 2 * data->eccentricity - ONE_HALF * data->eccentricity * cube(n)) +
                          (3.0 / 4.0) * (1 - square(theta) *
                          (2 * square(n) - data->eccentricity * n * data->eccentricity * cube(n)) *
                          cos(2 * data->perigee_arg))
                  ));
    double C_5 = 2 * q_0_minus_s_pow_4 * pow(epsilon, 4) * d_d_a_0 * square(beta_0) *
            pow(1 - square(n), -7.0 / 2.0) *
            (1 + (11.0 / 4.0) * n * (n + data->eccentricity) + data->eccentricity * cube(n));
    double D_2 = 4 * d_d_a_0 * epsilon * square(C_1);
    double D_3 = (4.0 / 3.0) * d_d_a_0 * square(epsilon) * (17 * d_d_a_0 + s) * cube(C_1);
    double D_4 = TWO_THIRDS * d_d_a_0 * cube(epsilon) * (221 * d_d_a_0 + 31 * s) * pow(C_1, 4);

}