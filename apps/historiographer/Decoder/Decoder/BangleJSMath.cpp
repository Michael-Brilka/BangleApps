#include "BangleJsMath.h"

//From https://github.com/espruino/Espruino/blob/master/src/jswrap_math.c#L267
//Used for calculating the height from the pressure after the Bangle js math.

double BangleJsMath::jswrap_math_mod(double x, double y) {
    double a, b;
    const double c = x;

    if (!isfinite(x) || isnan(y))
        return NAN;

    if (0 > c) {
        x = -x;
    }
    if (0 > y) {
        y = -y;
    }
    if (y != 0 && DBL_MAX >= y && DBL_MAX >= x) {
        while (x >= y) {
            a = x / 2;
            b = y;
            while (a >= b) {
                b *= 2;
            }
            x -= b;
        }
    }
    else {
        x = 0;
    }
    return 0 > c ? -x : x;
}

double BangleJsMath::jswrap_math_pow(double x, double y) {
    double p;
    /* quick hack for raising to a small integer power.
     * exp/log aren't accurate and are relatively slow, so
     * it's probably better to bash through small integer
     * powers in a stupid way. */
    int yi = (int)y;
    if (yi >= 0 && yi < 10 && yi == y) {
        if (yi == 0) return 1.0;
        p = x;
        while (yi > 1) {
            p *= x;
            yi--;
        }
        return p;
    }
    /* do proper floating point pow. Not as accurate as a
   * proper pow implementation but this saves a *lot*
   * of flash */
    if (x < 0 && jswrap_math_mod(y, 1) == 0) {
        if (jswrap_math_mod(y, 2) == 0) {
            p = exp(log(-x) * y);
        }
        else {
            p = -exp(log(-x) * y);
        }
    }
    else {
        if (x != 0 || 0 >= y) {
            p = exp(log(x) * y);
        }
        else {
            p = 0;
        }
    }
    return p;
}
