//
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
    struct net *net = malloc(sizeof(net));
    net->AS = MAX;
    net->E = 0;
    net->adj = (struct AS *) malloc(MAX * sizeof(struct AS));
    for (int i = 0; i < MAX; i++) {
        net->adj[i].head = NULL;
        net->adj[i].active = 0;
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
bool createEdge(struct net *net, int source, int destination, int type) {
    if (!net) return false;
    if (destination < 0 || destination >= MAX) return false;
    if (source < 0 || source >= MAX) return false;

    struct link *new = createAdjacency(destination, type);
    new->next = net->adj[source].head;
    net->adj[source].active = 1;
    net->adj[source].head = new;
    net->E++;

    return true;
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
struct link *createAdjacency(int destination, int type) {

    struct link *temp = malloc(sizeof(struct link));
    if (!temp) return NULL;

    temp->id = destination;
    temp->type = type;
    temp->next = NULL;
    return temp;
}

struct net* reverseNet(struct net* network) {
    struct net* reversed = createNet(network->AS, network->E);

    for (int i = 0; i < network->AS; i++) {
        struct link* curr = network->adj[i].head;
        while (curr != NULL) {
            // Reverse the edge and add to the reversed graph
            createEdge(reversed, curr->id, i, curr->type);
            curr = curr->next;
        }
    }

    return reversed;
}