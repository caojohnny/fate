#include <math.h>
#include "earth.h"
#include "util.h"

static const double SPHEROID_A = 6379.137;
static const double SPHEROID_B = 6356.7523;

static const double SPHEROID_A_SQ = SPHEROID_A * SPHEROID_A;
static const double SPHEROID_B_SQ = SPHEROID_B * SPHEROID_B;

double earth_radius(double latitude) {
    double rad = to_radians(latitude);
    double divisor = SPHEROID_A_SQ * SPHEROID_B_SQ;
    double dividend = (SPHEROID_A_SQ * square(sin(rad))) +
            (SPHEROID_B_SQ * square(cos(rad)));
    return sqrt(divisor / dividend);
}
