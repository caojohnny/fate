#include <math.h>
#include "astrotime.h"
#include "util.h"

gmst to_gmst(int year, int month, int day, int hour, int minute, int second) {
    year -= 1;
    long a = year / 100;
    long b = 2 - a + (a / 4);
    double jd_start_day = (long) (365.25 * year) + (long) (30.6001 * 14) + 1720994.5 + b;
    year += 1;

    static const int day_accum[2][13] = {
            { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
            { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 }
    };
    int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    int jd_day = day_accum[leap][month] + day;

    static const int seconds_per_day = 24 * 3600;
    int total_offset_seconds = hour * 3600 + minute * 60 + second;
    double jd_off = (double) total_offset_seconds / seconds_per_day;

    double jd = jd_start_day + jd_day + jd_off;

    double T = (jd - frac(jd + 0.5) - 2451545.0)/36525;
    double gwt0 = (24110.54841 + 8640184.812866 * T +0.093104 * square(T) - 0.0000062 * cube(T)) / 3600;
    double gw = 0;
    if (gwt0 >= 24) {
        gw = gwt0 - 24 * floor(gwt0 / 24);
    }
    if (gwt0 <= -24) {
        gw = 24 - (fabs(gwt0) - 24 * floor(fabs(gwt0) / 24));
    }
    double gmst = gw + 1.00273790935 * hour + minute * 60 + second * 3600;
    if (gmst >= 24) {
        gmst = gmst - 24;
    }
    if (gmst < 0) {
        gmst = gmst + 24;
    }
    return (gmst * M_PI / 12);
}
