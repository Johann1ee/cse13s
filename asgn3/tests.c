#include "mathlib.h"

#include <stdio.h>
#include <math.h>

int main(void) {
    //graphing sine
    FILE *Sine;

    Sine = fopen("sin.csv", "w");

    fprintf(Sine, "x, y\n");

    for (double x = 0; x <= 2.0 * M_PI; x += 0.1) {
        double y = Sin(x) - sin(x);

        fprintf(Sine, "%f, %.10f\n", x, y);
    }

    fclose(Sine);

    //graphing cosine
    FILE *Cosine;

    Cosine = fopen("cos.csv", "w");

    fprintf(Cosine, "x, y\n");

    for (double x = 0; x <= 2.0 * M_PI; x += 0.1) {
        double y = Cos(x) - cos(x);

        fprintf(Sine, "%f, %.10f\n", x, y);
    }

    fclose(Cosine);

    //graping tangent
    FILE *Tangent;

    Tangent = fopen("tan.csv", "w");

    fprintf(Tangent, "x, y\n");

    for (double x = 0; x <= 2.0 * M_PI; x += 0.1) {
        double y = Tan(x) - tan(x);

        fprintf(Sine, "%f, %.15f\n", x, y);
    }

    fclose(Tangent);

    return 0;
}
