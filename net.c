// Created by guilh on 10/09/2024.
//

#include <stdio.h>
#include <stdlib.h>

#include "header.h"

/**
 * @brief Creates and initializes a network structure.
 *
 * This function allocates memory for a new net structure, sets the AS (Autonomous System) count to MAX,
 * initializes the edge count to 0, and allocates memory for the adjacency list. Each entry in the adjacency
 * list is also initialized.
 *
 * @return A pointer to the newly created net structure. The caller is responsible for freeing this memory.
 */
struct net *createNet() {
    struct net *net = malloc(sizeof(struct net));
    net->E = 0;
    net->V = 0;
    for (int i = 0; i < MAX; i++) {
        net->adj[i] = NULL;
    }
    return net;
}
/**
 * @brief Creates an edge in the network structure.
 *
 * This function adds a new edge to the network by updating the adjacency list for the specified source node.
 * The edge is defined by a source node, a destination node, and a type.
 *
 * @param net Pointer to the network structure.
 * @param source The source node of the edge.
 * @param destination The destination node of the edge.
 * @param type The type of the edge.
 * @return True if the edge was successfully created, otherwise false.
 */

void createEdge(struct net *network, int source, int destination, int type) {
    struct link *newLink = malloc(sizeof(struct link));
    if (network->adj[source]==NULL) {
        network->V++;
    }
    network->E++;
    newLink->id = destination;
    newLink->type = type;
    newLink->next = network->adj[source];
    network->adj[source] = newLink;

}

void removeEdge(struct net *network, int source, int destination) {
    struct link **curr = &network->adj[source];
    while (*curr != NULL) {
        if ((*curr)->id == destination) {
            struct link *toRemove = *curr;
            *curr = (*curr)->next;
            free(toRemove);
            break;
        }
        curr = &(*curr)->next;
    }
}

/**
 * @brief Creates an adjacency link to a destination.
 *
 * This function allocates memory for a new link structure and initializes it with
 * the given destination ID and type. The next pointer is set to NULL.
 *
 * @param destination The destination ID for the adjacency link.
 * @param type The type associated with the adjacency link.
 *
 * @return A pointer to the newly created link structure, or NULL if memory allocation fails.
 *         The caller is responsible for freeing this memory.
 */


void freeNet(struct net *net) {
    if (net == NULL) {
        return;  // Nothing to free if net is NULL
    }

    // Free each adjacency list
    for (int i = 0; i < MAX; i++) {
        struct link *current = net->adj[i];
        while (current != NULL) {
            struct link *temp = current;  // Save the current node
            current = current->next;      // Move to the next node
            free(temp);                   // Free the saved node
        }
    }

    // Free the network structure itself
    free(net);
}