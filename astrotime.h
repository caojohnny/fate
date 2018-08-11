#ifndef FATE_ASTROTIME_H
#define FATE_ASTROTIME_H

/**
 * GMST represented as a radian measure in a double
 */
typedef double gmst;

/**
 * Converts the given Gregorian time measurements (i.e.
 * standard calendar measurements) into GMST, represented
 * as a radian value.
 *
 * @param year the year which to convert
 * @param month the month
 * @param day the day
 * @param hour the hour in UTC
 * @param minute the minute in UTC
 * @param second the second in UTC
 * @return the GMST time
 */
gmst to_gmst(int year, int month, int day, int hour, int minute, int second);

#endif /* FATE_ASTROTIME_H */
