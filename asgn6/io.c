#include "io.h"

#include <stdlib.h>

void read_uint8(FILE *fin, uint8_t *px) {
    int result = fgetc(fin);
    if (result == EOF) {
        fprintf(stderr, "fatal error read\n");
        exit(1);
    }
    *px = (uint8_t) result;
}

void read_uint16(FILE *fin, uint16_t *px) {
    uint8_t temp1, temp2;

    read_uint8(fin, &temp1);
    read_uint8(fin, &temp2);

    *px = temp2 << 8;
    *px = *px | temp1;
}

void read_uint32(FILE *fin, uint32_t *px) {
    uint16_t temp1, temp2;

    read_uint16(fin, &temp1);
    read_uint16(fin, &temp2);

    *px = temp2 << 16;
    *px = *px | temp1;
}

void write_uint8(FILE *fout, uint8_t x) {
    int result = fputc(x, fout);
    if (result == EOF) {
        fprintf(stderr, "fatal error write\n");
        exit(1);
    }
}

void write_uint16(FILE *fout, uint16_t x) {
    write_uint8(fout, x);
    write_uint8(fout, x >> 8);
}

void write_uint32(FILE *fout, uint32_t x) {
    write_uint16(fout, x);
    write_uint16(fout, x >> 16);
}
