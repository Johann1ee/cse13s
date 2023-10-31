#include "stack.h"

#include "mathlib.h"
#include "messages.h"

#include <stdbool.h>
#include <stdio.h>

int top = -1;

bool stack_push(double item) {
    if (stack_size >= STACK_CAPACITY) {
        fprintf(stderr, ERROR_NO_SPACE, item);
        return false;
    } else {
        stack_size++;
        top++;
        stack[top] = item;
	printf("%f", item);
        return true;
    }
}

bool stack_pop(double *item) {
    if (stack_size == 0) {
        return false;
    } else {
        *item = stack[top];
        top--;
        stack_size--;
        return true;
    }
}

bool stack_peek(double *item) {
    if (stack_size == 0) {
        return false;
    } else {
        *item = stack[stack_size];
        return true;
    }
}

void stack_clear(void) {
    stack_size = 0;
    top = -1;
}

void stack_print(void) {
    // make sure we don't print stack[0] when it is empty
    if (stack_size == 0) {
        return;
    }
    // print the first element with 10 decimal places
    printf("%.10f", stack[0]);
    // print the remaining elements (if any), with a space before each one
    for (int i = 1; i < stack_size; i++) {
        printf(" %.10f", stack[i]);
    }
}
