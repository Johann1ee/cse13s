#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int opt;
    bool my_math = true;

    while ((opt = getopt(argc, argv, "hm")) != -1) {
        switch (opt) {
        case 'm': my_math = false; break;
        case 'h': printf(USAGE, "./calc"); return 0;
        case '?': break;
        }
    }

    while (1) {
        char expr[1024];
        char *saveptr;
        bool error = false;
        double holder;

        fprintf(stderr, "> ");
        if (fgets(expr, sizeof(expr), stdin) != NULL) {
            size_t len = strlen(expr);

            if (len > 0 && expr[len - 1] == '\n') {
                expr[len - 1] = '\0';
            }
        } else {
            return 0;
        }

        const char *token = strtok_r(expr, " ", &saveptr);

        while (token != NULL && !error) {
            int bin = 0, unary = 0;
            int pocket = (int) strlen(token);

            for (int i = 0; i < 256; i++) {
                if (binary_operators[i] != NULL && i == *token && pocket == 1) {
                    bin = 1;
                    break;
                }
            }
            for (int i = 0; i < 256; i++) {
                if (my_unary_operators[i] != NULL && i == *token && pocket == 1) {
                    unary = 1;
                    break;
                }
            }

            if (!parse_double(token, &holder) && bin == 0 && unary == 0) {
                if (strlen(token) == 1) {
                    fprintf(stderr, ERROR_BAD_CHAR, token[0]);
                    error = true;
                } else {
                    fprintf(stderr, ERROR_BAD_STRING, token);
                    error = true;
                }
            }
            if (parse_double(token, &holder)) {
                if (!stack_push(holder)) {
                    error = true;
                }
            }

            if (bin == 1) {
                switch (token[0]) {
                case '+':
                    if (!apply_binary_operator(operator_add)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        error = true;
                    }
                    break;
                case '-':
                    if (!apply_binary_operator(operator_sub)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        error = true;
                    }
                    break;
                case '*':
                    if (!apply_binary_operator(operator_mul)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        error = true;
                    }
                    break;
                case '/':
                    if (!apply_binary_operator(operator_div)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        error = true;
                    }
                    break;
                case '%':
                    if (!apply_binary_operator(fmod)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        error = true;
                    }
                    break;
                }
            }
            if (unary == 1 && my_math == true) {
                switch (token[0]) {
                case 's':
                    if (!apply_unary_operator(Sin)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    }
                    break;
                case 'c':
                    if (!apply_unary_operator(Cos)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    }
                    break;
                case 't':
                    if (!apply_unary_operator(Tan)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    }
                    break;
                case 'a':
                    if (!apply_unary_operator(Abs)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    }
                    break;
                case 'r':
                    if (!apply_unary_operator(Sqrt)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    }
                    break;
                }
            }
            if (unary == 1 && my_math == false) {
                switch (token[0]) {
                case 's':
                    if (!apply_unary_operator(sin)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    }
                    break;
                case 'c':
                    if (!apply_unary_operator(cos)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    }
                    break;
                case 't':
                    if (!apply_unary_operator(tan)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    }
                    break;
                case 'a':
                    if (!apply_unary_operator(fabs)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    }
                    break;
                case 'r':
                    if (!apply_unary_operator(sqrt)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    }
                    break;
                }
            }
            token = strtok_r(NULL, " ", &saveptr);
        }

        if (error == false) {
            stack_print();
            printf("%c", '\n');
        }
        stack_clear();
    }

    return 0;
}
