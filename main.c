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
                    if(net2->adj[t]==NULL){
                        printf("%d is not a possible destination\n",t);
                        continue;
                    }
                    clock_t before1 = clock();
                    Commercial(net, t, 0);
                    clock_t after1 = clock(); // Get the time after the function call
                    int msec1 = (after1 - before1) * 1000 / CLOCKS_PER_SEC; // Convert time to milliseconds
                    printf("Time taken: %d minutes %d seconds %d milliseconds\n",
                           msec1 / 60000, (msec1 / 1000) % 60, msec1 % 1000);
                }
                break;
            case 2:
                CommercialCycle();
                break;
            case 3:
                CommercialConnected();
                break;
            case 4:
                clock_t before4 = clock();
                CommercialAll(net);
                clock_t after4 = clock(); // Get the time after the function call
                int msec4 = (after4 - before4) * 1000 / CLOCKS_PER_SEC; // Convert time to milliseconds
                printf("Time taken: %d minutes %d seconds %d milliseconds\n",
                       msec4 / 60000, (msec4 / 1000) % 60, msec4 % 1000);
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
                clock_t before7 = clock();
                CommercialLengthsAll(net2);
                clock_t after7 = clock(); // Get the time after the function call
                int msec7 = (after7 - before7) * 1000 / CLOCKS_PER_SEC; // Convert time to milliseconds
                printf("Time taken: %d minutes %d seconds %d milliseconds\n",
                       msec7 / 60000, (msec7 / 1000) % 60, msec7 % 1000);
                break;
            case 8:
                clock_t before8 = clock();
                ShortestAll(net2);
                clock_t after8 = clock(); // Get the time after the function call
                int msec8 = (after8 - before8) * 1000 / CLOCKS_PER_SEC; // Convert time to milliseconds
                printf("Time taken: %d minutes %d seconds %d milliseconds\n",
                       msec8 / 60000, (msec8 / 1000) % 60, msec8 % 1000);
                break;
            default:
                freeNet(net);
                freeNet(net2);
                return 0;
        }
    }
    return EXIT_SUCCESS;
}
