#include "bmp.h"
#include "io.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HELPMESSAGE "Usage: colorb -i infile -o outfile\n       colorb -h\n"

int main(int argc, char *argv[]) {
    int opt;
    char *chinfile = NULL;
    char *choutfile = NULL;

    while ((opt = getopt(argc, argv, "hi:o:")) != -1) {
        if (argc < 2) {
            fprintf(stderr, "colorb: -i option is required\n");
            printf(HELPMESSAGE);
            exit(1);
        }
        switch (opt) {
        case 'h': printf(HELPMESSAGE); return 0;
        case 'i': chinfile = optarg; break;
        case 'o': choutfile = optarg; break;
        }
    }

    if (chinfile == NULL) {
        fprintf(stderr, "colorb:  -i option is required\n");
        printf(HELPMESSAGE);
        exit(1);
    }
    if (choutfile == NULL) {
        fprintf(stderr, "colorb:  -o option is required\n");
        printf(HELPMESSAGE);
        exit(1);
    }

    FILE *infile = fopen(chinfile, "rb");
    if (infile == NULL) {
        fprintf(stderr, "colorb:  unknown or poorly formatted option -i\n");
        printf(HELPMESSAGE);
        fclose(infile);
        exit(1);
    }

    FILE *outfile = fopen(choutfile, "wb");
    if (outfile == NULL) {
        fprintf(stderr, "colorb:  unknown or poorly formatted option -o\n");
        printf(HELPMESSAGE);
        fclose(outfile);
        exit(1);
    }

    BMP *colorImage = bmp_create(infile);
    bmp_reduce_palette(colorImage);
    bmp_write(colorImage, outfile);

    bmp_free(&colorImage);
    if (infile != NULL) {
        fclose(infile);
    }
    if (outfile != NULL) {
        fclose(outfile);
    }
    return 0;
}
