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

//This function was given to us by Kerry Veenstra asgn3.pdf page 4
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
    x = fmod(x, 2.0 * M_PI);

    int n = 1;
    double rad = x;
    double holder = x;
    int swap = -1;

    while (1) {
        holder = holder * ((x * x) / ((2 * n) * (2 * n + 1)));
        rad += swap * holder;
        swap = -swap;
        n++;

        if (Abs(holder) < EPSILON) {
            holder = holder * ((x * x) / ((2 * n) * (2 * n + 1)));
            rad += swap * holder;
            break;
        }
    }
    rad = fmod(rad, 2.0 * M_PI);

    return rad;
}

double Cos(double x) {
    x = fmod(x, 2.0 * M_PI);

    int n = 1;
    double rad = 1.0;
    double holder = 1.0;
    int swap = -1;

    while (1) {
        holder = holder * ((x * x) / ((n + (n - 1)) * (2 * n)));
        rad += swap * holder;
        swap = -swap;
        n++;

        if (Abs(holder) < EPSILON) {
            holder = holder * ((x * x) / ((n + (n - 1)) * (2 * n)));
            rad += swap * holder;
            break;
        }
    }
    rad = fmod(rad, 2.0 * M_PI);

    return rad;
}

double Tan(double x) {
    double z = (Sin(x) / Cos(x));
    return z;
}
