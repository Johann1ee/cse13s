#include "mathlib.h"

#include <math.h>
#include <stdio.h>

double Abs(double x) {
    double y = x * x;
    y = Sqrt(y);
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
    double z = 0;
    int n = 0;

    while (1) {
        double a, b = 1, c = x, d;

        if (fmod(n, 2) == 0) {
            a = 1;
        } else {
            a = -1;
        }

        for (int i = 1; i <= (2 * n + 1); i++) {
            b = b * i;
        }

        for (int i = 1; i <= (2 * n + 1); i++) {
            c = c * x;
        }

        d = (a / b) * c;

        if (d < EPSILON) {
            break;
        }

        z = z + d;
        n++;
    }

    double twopi = 2.0 * M_PI;

    while (z < 0.0) {
        z -= twopi;
    }
    while (z > twopi) {
        z += twopi;
    }

    return z;
}

double Cos(double x) {
    double z = 0;
    int n = 0;

    while (1) {
        double a, b = 1, c = x, d;

        if (fmod(n, 2) == 0) {
            a = 1;
        } else {
            a = -1;
        }

        for (int i = 1; i <= (2 * n); i++) {
            b = b * i;
        }

        for (int i = 1; i <= (2 * n); i++) {
            c = c * x;
        }

        d = (a / b) * c;

        if (d < EPSILON) {
            break;
        }

        z = z + d;
        n++;
    }

    double twopi = 2.0 * M_PI;

    while (z < 0.0) {
        z -= twopi;
    }
    while (z > twopi) {
        z += twopi;
    }

    return z;
}

double Tan(double x) {
    double z = (Sin(x) / Cos(x));
    return z;
}
