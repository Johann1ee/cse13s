CC=clang
CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic -gdwarf-4
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
