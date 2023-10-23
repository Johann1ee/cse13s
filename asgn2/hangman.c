#include "hangman_helpers.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "wrong number of arguements\n"
                        "usage: ./hangman <secrete word or phrase>\n"
                        "if the secret is multiple words, you must quote it\n");
        exit(1);
    }
    if (validate_secret(argv[1]) == false) {
        exit(1);
    }

    int mistake = 0;
    int length = (int) strlen(argv[1]);
    char phrase[256] = { 0 };
    char eliminated[26] = { 0 };
    strncpy(phrase, argv[1], (size_t) length);
    char guess;
    char *t = phrase;
    char alph[26] = { 0 };
    char *b = alph;

    for (int i = 0; i < length; ++i) {
        if (is_lowercase_letter(*t) == true) {
            *t = '_';
        }
        t++;
    }

    while (mistake < LOSING_MISTAKE) {
        if (strcmp(phrase, argv[1]) == 0) {
            break;
        }
        printf("%s", CLEAR_SCREEN);
        printf("%s\n", arts[mistake]);
        printf("\n    Phrase: %s\n", phrase);
        printf("Eliminated: ");
        for (int i = 0; i < 26; i++) {
            if (eliminated[i] == 1) {
                printf("%c", 'a' + i);
            }
        }
        printf("\n\n");

        do {
            guess = read_letter();
        } while (!is_lowercase_letter(guess));

        if (string_contains_character(argv[1], guess) == true) {
            for (int i = 0; i < length; ++i) {
                if (guess == argv[1][i]) {
                    phrase[i] = guess;
                }
            }
        } else {
            if (string_contains_character(alph, guess) == false) {
                eliminated[guess - 'a'] = 1;
                mistake++;
                for (int i = 0; i < 26; ++i) {
                    if (eliminated[i] == 1) {
                        *b = (char) i + 'a';
                        b++;
                    }
                }
            }
        }
    }

    printf("%s", CLEAR_SCREEN);
    printf("%s\n\n", arts[mistake]);
    if (mistake >= LOSING_MISTAKE) {
        printf("    Phrase: %s\n", phrase);
        printf("Eliminated: ");
        for (int i = 0; i < 26; i++) {
            if (eliminated[i] == 1) {
                printf("%c", 'a' + i);
            }
        }
        printf("\n\nYou lose! The secret phrase was: %s\n", argv[1]);
    } else {
        printf("    Phrase: %s\n", phrase);
        printf("Eliminated: ");
        for (int i = 0; i < 26; i++) {
            if (eliminated[i] == 1) {
                printf("%c", 'a' + i);
            }
        }
        printf("\n\nYou win! The secret phrase was: %s\n", argv[1]);
    }

    return 0;
}
