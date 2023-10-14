#include <stdio.h>
#include <stdlib.h>
#include "names.h"

int main(void) {

    /* pig array that will be used for random() */
    typedef enum {SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER} Position;
    const Position pig[7] = {
            SIDE,
            SIDE,
            RAZORBACK,
            TROTTER,
            SNOUTER,
            JOWLER,
            JOWLER,
    };

    /* grab the needed number of players from the user
       then check to make sure the input is within edge */
    int number_players = 2;
    printf("Number of players (2 to 10)? ");
    int player_scan = scanf("%d", &number_players);

    if (player_scan < 1 || number_players < 2 || number_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        number_players = 2;
    }

    /* grab the needed random seed from the user
       then edge case again for errors */
    unsigned seed = 2023;
    printf("Random-number seed? ");
    int seed_scan = scanf("%u", &seed);

    if (seed_scan < 1) {
        fprintf(stderr, "Invalid seed. Using 2023 instead.\n");
        seed = 2023;
    }
    srandom(seed);

    /* creates a new array based on keeping track of scores
       with a matching index to the player */
    int player_score[10] = {
            0,
    };

    for (int i = 0; i < number_players; i++) {
        player_score[i] = 0;
    }

    /* while loop for game to take place within */
    int max = 0;
    do {

        /* for loop to run through each player's
         * turn for rolling the pig */

        for (int i = 0; i < number_players; ++i) {

            /* print current player name and initialize
             * pig_set which holds the current
             * enum pig value */

            printf("%s\n", player_name[i]);
            int pig_set = -1;

            /* while loop which runs for until player
             * rolls a side pig with switch case for
             * each different kind of pig roll*/

            while (pig_set != 0) {

                pig_set = pig[random() % 7];

                switch (pig_set) {
                    case 0:
                        printf(" rolls %d, has %d\n", pig_set, player_score[i]);
                        break;
                    case 1:
                        player_score[i] += 10;
                        printf(" rolls 10, has %d\n", player_score[i]);
                        break;
                    case 2:
                        player_score[i] += 10;
                        printf(" rolls 10, has %d\n", player_score[i]);
                        break;
                    case 3:
                        player_score[i] += 15;
                        printf(" rolls 15, has %d\n", player_score[i]);
                        break;
                    case 4:
                        player_score[i] += 5;
                        printf(" rolls 5, has %d\n", player_score[i]);
                        break;
                }
                if (player_score[i] >= 100){
                    printf("%s won!\n", player_name[i]);
                    return 0;
                }
            }

        }
    } while (max <= 100);
}

