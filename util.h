#ifndef FATE_UTIL_H
#define FATE_UTIL_H

#include <math.h>

/*
 * Multiplies the given number by itself.
 *
 * CONSTRAINT: x <= 1.34E154
 */
inline double square(double x) {
    return x * x;
}

/*
 * Converts the given number to radians.
 *
 * CONSTRAINT: x is in degrees
 * CONSTRAINT: x <= 1.14E306
 */
inline double to_radians(double x) {
    static const double MULTIPLIER = M_PI / 180;

    return x * MULTIPLIER;
}

#endif /* FATE_UTIL_H */
