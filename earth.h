#ifndef FATE_EARTH_H
#define FATE_EARTH_H

/*
 * Calculates the approximate radius of the earth at the
 * given latitude in degrees
 *
 * CONSTRAINT: latitude in degrees
 * CONSTRAINT: -90 <= latitude
 * CONSTRAINT: latitude <= 90
 */
double earth_radius(double);

#endif /* FATE_EARTH_H */
