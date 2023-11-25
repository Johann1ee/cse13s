CC=clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic

EXECBIN= xd
OBJS= xd.o

all: xd 

$(EXECBIN): $(OBJS)
	$(CC) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJS) $(TESTBIN) $(TESTOBJS)

format:
	clang-format -i --style=file *.[ch]

.PHONY: all debug release clean
