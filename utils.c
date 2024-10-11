#include "header.h"
#include <stdio.h>

/**
 * Opens a file and reads network data into a net structure.
 *
 * @param filename Pointer to a character array specifying the file to be opened.
 * @param net Pointer to a net structure where the network data will be stored.
 * @return A pointer to the net structure with the loaded data, or NULL if the file could not be opened.
 */
struct net *OpenFile(const char *filename, struct net *net) {

    FILE *file = NULL;
    int source, destination, type;
    if (!((file = fopen(filename, "r")))) return NULL;

    net = createNet();
    while (fscanf(file, "%d %d %d", &source, &destination, &type) == 3) {
        createEdge(net, source, destination, type);
    }
    findStronglyConnectedComponents(net);
    connectAnalysis(net);
    fclose(file);
    return net;
}

/**
 * By knowing the previous path type, it calculates whether a link is valid or not
 *
 * @param prevType Type of path that has lead to the current node.
 * @param currentType Type of path that is about to be checked to go on
 * @return An integer corresponding to the type of path to follow if valid, or 0 otherwise.
 */
int isValidRoute(const int prevType, const int currentType) {
    return prevType == -1 || prevType == 0 || prevType == 3 || currentType == 1 ? currentType : 0;
}
