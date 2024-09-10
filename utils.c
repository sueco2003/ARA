//
// Created by guilh on 10/09/2024.
//

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
    return net;
}
