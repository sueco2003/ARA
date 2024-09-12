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
int main() {
    int option = 0;
    struct net *net = NULL;
    while ((option = interface()) != -1) {
        int t = 0;
        char input[100];

        switch (option) {
            case 1:
                printf("Please insert the net filename and target AS:\n");
            fflush(stdin);
                if (fscanf(stdin, "%s\n%d", input, &t) != 2) {
                    printf("Please provide the input needed!\n");
                }
                if (!((net = OpenFile(input, net)))) {
                    printf("Error opening file\n");
                    break;
                }
                Commercial(net, t);
                break;
            case 2:
                printf("Please insert the net filename: ");
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%d", &option) != 1) {
                    printf("Please provide the input needed!\n");
                }
                if (!((net = OpenFile(input, net)))) {
                    printf("Error opening file\n");
                    break;
                }
                CommercialCycle(net);
                break;
            case 3:
                printf("Please insert the net filename: ");
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%d", &option) != 1) {
                    printf("Please provide the input needed!\n");
                }
                if (!((net = OpenFile(input, net)))) {
                    printf("Error opening file\n");
                    break;
                }
                CommercialConnected(net);
                break;
            case 4:
                printf("Please insert the net filename and target AS: ");
                if (fscanf(stdin, "%s\n%d", input, &option) != 2) {
                    printf("Please provide the input needed!\n");
                }
                if (!((net = OpenFile(input, net)))) {
                    printf("Error opening file\n");
                    break;
                }
                CommercialLengths(net, t);
                break;
            case 5:
                printf("Please insert the net filename: ");
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%d", &option) != 1) {
                    printf("Please provide the input needed!\n");
                }
                if (!((net = OpenFile(input, net)))) {
                    printf("Error opening file\n");
                    break;
                }
                CommercialLengthsAll(net);
                break;
            case 6:
                printf("Please insert the net filename: ");
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%d", &option) != 1) {
                    printf("Please provide the input needed!\n");
                }
                if (!((net = OpenFile(input, net)))) {
                    printf("Error opening file\n");
                    break;
                }
                ShortestAll(net);
                break;
            default: ;
        }
    }
    return EXIT_SUCCESS;
}