CC     = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -gdwarf-4
EXEC   = tsp
OBJS   = tsp.o graph.o path.o stack.o

all: tsp

tsp: $(OBJS)
	$(CC) -o tsp $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f tsp  $(OBJS)

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build --use-cc=$(CC) make

.PHONY: all clean format
