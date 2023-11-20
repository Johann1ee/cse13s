CC=clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm

EXECBIN=colorb
OBJS= colorb.o io.o bmp.o 
TESTBIN=iotest
TESTOBJS= io.o iotest.o

all: colorb iotest

$(EXECBIN): $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

$(TESTBIN): $(TESTOBJS)
	$(CC) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJS) $(TESTBIN) $(TESTOBJS)

format:
	clang-format -i --style=file *.[ch]

.PHONY: all debug release clean
