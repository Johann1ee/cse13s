#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define n size_t
#define a 16
#define m printf
#define y c[i]
void z(char c[a], int f, n e) {
    m("%08x: ", f);
    for (n i = 0; i < a; i++) {
        m((i < e) ? "%02x" : "  ", (unsigned char) y);
        m((i % 2 == 1) ? " " : 0);
    }
    for (n i = 0; i < a; i++)
        y = (y < 32 || y >= 127) ? '.' : y;
    m(" ");
    for (n i = 0; i < e; i++)
        putchar(y);
    m("\n");
}
int main(int g, char *h[]) {
    int b = 0, f = 0;
    char c[a];
    n d = 0, e = 0;
    if (g == 2)
        b = open(h[1], O_RDONLY, 0);
    if (b == -1)
        return 1;
    while ((d = (n) read(b, c + e, a - e)) > 0) {
        e += (n) d;
        if (e == a) {
            z(c, f, e);
            e = 0;
            f += a;
        }
    }
    if (e > 0) {
        z(c, f, e);
    }
    close(b);
    return 0;
}
