#include <math.h>
#include "earth.h"
#include "util.h"

static const double SPHEROID_A_SQ = 6379.137 * 6379.137;
static const double SPHEROID_B_SQ = 6356.7523 * 6356.7523;

double earth_radius(double latitude) {
    double rad = to_radians(latitude);
    double divisor = SPHEROID_A_SQ * SPHEROID_B_SQ;
    double dividend = (SPHEROID_A_SQ * square(sin(rad))) +
            (SPHEROID_B_SQ * square(cos(rad)));
    return sqrt(divisor / dividend);
}
