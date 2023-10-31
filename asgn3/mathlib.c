#include "mathlib.h"

#include <math.h>
#include <stdio.h>

double Abs(double x) {
    double y;
    if (x > 0) {
        y = x;
    } else {
        y = -x;
    }
    return y;
}

double Sqrt(double x) {
    // Check domain.
    if (x < 0) {
        return nan("nan");
    }

    double old = 0.0;
    double new = 1.0;

    while (Abs(old - new) > EPSILON) {
        // Specifically, this is the Babylonian method--a simplification of
        // Newton's method possible only for Sqrt(x).
        old = new;
        new = 0.5 * (old + (x / old));
    }

    return new;
}

double Sin(double x) {
    int n = 1;
    double rad = x;
    double holder = x;
    int swap = -1;

    while (1) {
	if (Abs(holder) < (EPSILON / 1000000)){
		break;
	}

        holder = holder * ((x * x) / ((2 * n) * (2 * n + 1)));
        rad += swap * holder;
        swap = -swap;
        n++;
    }
    double twopi = 2.0 * M_PI;
    rad = fmod(rad, twopi);

    return rad;
}

double Cos(double x) {
    int n = 1;
    double rad = 1.0;
    double holder = 1.0;
    int swap = -1;

    while (1) {
        if (Abs(holder) < (EPSILON / 100000)0) {
            break;
        }

        holder = holder * ((x * x) / ((n + (n - 1)) * (2 * n)));
        rad += swap * holder;
        swap = -swap;
        n++;
    }
    double twopi = 2.0 * M_PI;
    rad = fmod(rad, twopi);

    return rad;
}

double Tan(double x) {
    double z = (Sin(x) / Cos(x));
    return z;
}
