#include "header.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * Displays a menu of algorithm options and prompts the user to select an option.
 * Continues to prompt the user until a valid option is selected.
 *
 * @return The selected option as an integer.
 */
int interface() {
    int option;
    do {
        printf("Welcome to ARA 24/25 algorithm collection\n\n");
        printf("1: COMMERCIAL(Net,t)\n");
        printf("2: COMMERCIAL(Net,t) [TEST]\n");
        printf("3: COMMERCIALCYCLE(Net)\n");
        printf("4: COMMERCIALCONNECTED(Net) \n");
        printf("5: COMMERCIALALL(Net) \n");
        printf("6: COMMERCIALLENGTHS(Net,t)\n");
        printf("7: COMMERCIALLENGTHSALL(Net)\n");
        printf("8: SHORTESTALL(Net)\n\n");
        printf("Please select an option (Enter -1 to leave):\n");
        if (fscanf(stdin, "%d", &option) != 1) {
            printf("Please input a number!\n");
        }
        if (option == -1) {
            return 0;
        }
        
    } while (option < 1 || option > 7);
    return option;
}