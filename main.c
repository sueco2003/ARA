#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"
/**
 * @brief Main entry point of the program that provides an interface to perform various network operations.
 *
 * The main function continuously prompts the user to select an option to perform different network-related
 * operations until the user decides to exit by selecting the appropriate option. The operations include:
 * - Opening a network file and performing commercial analysis for a given target AS.
 * - Opening a network file and checking for commercial cycles.
 * - Opening a network file and checking commercial connectivity.
 * - Opening a network file and calculating commercial lengths for a given target AS.
 * - Opening a network file and calculating commercial lengths for all AS.
 * - Opening a network file and finding the shortest paths.
 *
 * The program expects user input for filenames and target AS parameters as needed by the selected operations.
 * @return EXIT_SUCCESS if the program completes successfully.
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid inputs\n");
        exit(1);
    }
    struct net *net = NULL;
    struct net *net2 = NULL;
    if (!((net = OpenFile(argv[1], net,&net2)))) {
        printf("Error opening file\n");
        exit(1);
    }

    int option = 0;
    while ((option = interface()) != -1) {
        int t = 0;

        switch (option) {
            case 1:
                printf("Please insert the target AS:\n");
                if (fscanf(stdin, "%d", &t) != 1) {
                    printf("Please provide the input needed!\n");
                } else {
                    clock_t before = clock();
                    Commercial(net, t, 0);
                    clock_t after = clock(); // Get the time after the function call
                    int msec = (after - before) * 1000 / CLOCKS_PER_SEC; // Convert time to milliseconds
                    printf("Time taken: %d minutes %d seconds %d milliseconds\n",
                           msec / 60000, (msec / 1000) % 60, msec % 1000);
                }
                break;
            case 2:
                CommercialCycle();
                break;
            case 3:
                CommercialConnected();
                break;
            case 4:
                clock_t before = clock();
                CommercialAll(net);
                clock_t after = clock(); // Get the time after the function call
                int msec = (after - before) * 1000 / CLOCKS_PER_SEC; // Convert time to milliseconds
                printf("Time taken: %d minutes %d seconds %d milliseconds\n",
                       msec / 60000, (msec / 1000) % 60, msec % 1000);
                break;
            case 5:
                printf("Please insert the target AS:\n");
                if (fscanf(stdin, "%d", &t) != 1) {
                    printf("Please provide the input needed!\n");
                }else{
                    CommercialLengths(net2, t);
                }
                break;
            case 6:
                printf("Please insert the target AS:\n");
                if (fscanf(stdin, "%d", &t) != 1) {
                    printf("Please provide the input needed!\n");
                }else{
                    CommercialLengthsTest(net2, t);
                }
                break;
            case 7:
                CommercialLengthsAll(net2);
                break;
            case 8:
                ShortestAll(net2);
                break;
            default:
                freeNet(net);
                freeNet(net2);
                return 0;
        }
    }
    return EXIT_SUCCESS;
}
