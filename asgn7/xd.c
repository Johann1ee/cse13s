#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE (size_t) 16

int main(int argc, char *argv[]) {
    int fd = 0;
    char buffer[BUFFER_SIZE];
    ssize_t reader = 0;
    size_t readBytes = 0;
    int index = 0;

    //if there is a file attached it changes the open path
    //to the file
    if (argc == 2) {
        fd = open(argv[1], O_RDONLY, 0);

        if (fd == -1) {
            exit(1);
        }
    } //Since fd is initialized at 0 it takes from stdin by default

    while ((reader = read(fd, buffer + readBytes, BUFFER_SIZE - readBytes)) > 0) {
        readBytes += (size_t) reader;

        //check if buffer is full
        if (readBytes == BUFFER_SIZE) {

            printf("%08x: ", index);
            for (size_t i = 0; i < readBytes; i++) {
                printf("%02x", (unsigned char) buffer[i]);
                if (i % 2 == 1) {
                    printf(" ");
                }
            }

            for (size_t i = 0; i < BUFFER_SIZE; i++) {
                if (buffer[i] < 32 || buffer[i] >= 127) {
                    buffer[i] = '.';
                }
            }

            printf(" %.16s\n", buffer);

            //new line and reset readBytes
            readBytes = 0;
            index += 16;
        }
    }

    if (readBytes > 0) {

        printf("%08x: ", index);
        for (size_t i = 0; i < BUFFER_SIZE; i++) {
            if (i < readBytes) {
                printf("%02x", (unsigned char) buffer[i]);
            } else
                printf("  ");
            if (i % 2 == 1) {
                printf(" ");
            }
        }
        for (size_t i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] < 32 || buffer[i] >= 127) {
                buffer[i] = '.';
            }
        }

        printf(" ");
        for (size_t i = 0; i < readBytes; i++) {
            putchar(buffer[i]);
        }
        printf("\n");
    }
    close(fd);

    return 0;
}
