CC     = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic 
LFLAGS = -lm 
EXEC   = calc
CALC_OBJS   = calc.o stack.o mathlib.o operators.o
TESTS_OBJS = tests.o mathlib.o
TESTS_PROD = sin.csv cos.csv tan.csv

all: calc tests

calc: $(CALC_OBJS)
	$(CC) $(LFLAGS) -o calc $(CALC_OBJS)

tests: $(TESTS_OBJS)
	$(CC) $(LFLAGS) -o tests $(TESTS_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f calc tests $(CALC_OBJS) $(TESTS_OBJS) $(TESTS_PROD)

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build --use-cc=$(CC) make

.PHONY: all clean format


