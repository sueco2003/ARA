#include <stdio.h>
#include <stdlib.h>
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


    if(argc !=2){
        printf("Invalid inputs\n");
        exit(1);
    }
    struct net *net = NULL;
    if (!((net = OpenFile(argv[1], net)))) {
        printf("Error opening file\n");
        exit(1);
    }

    int option = 0;
    while ((option = interface()) != -1) {
        int t = 0;
        int s=0;
        char input[100];

        switch (option) {
            case 1:
                printf("Please insert the target AS:\n");
                if (fscanf(stdin, "%d", &t) != 1) {
                    printf("Please provide the input needed!\n");
                }else{
                    Commercial(net, t);
                }
                break;
            case 2:
                printf("Please insert the source and destination AS:\n");
                if (fscanf(stdin, "%d %d", &s, &t) != 1) {
                    printf("Please provide the input needed!\n");
                }else{
                    CommercialTest(net, s, t);
                }
                break;
            case 3:
                CommercialCycle(net);
                break;
            case 4:
                CommercialConnected(net);
                break;
            case 5:
                CommercialLengths(net, t);
                break;
            case 6:
                CommercialLengthsAll(net);
                break;
            case 7:
                ShortestAll(net);
                break;
            default: ;
        }
    }
    return EXIT_SUCCESS;
}