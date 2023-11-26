CC=clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic

EXECBIN= xd
OBJS= xd.o
SPAREBIN= bad_xd
SPAREOBJS= bad_xd.o

all: xd bad_xd

$(EXECBIN): $(OBJS)
	$(CC) -o $@ $^

$(SPAREBIN): $(SPAREOBJS)
	$(CC) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJS) $(SPAREBIN) $(SPAREOBJS)

format:
	clang-format -i --style=file *.[ch]

.PHONY: all debug release clean
