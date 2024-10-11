#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/**
 * Using a Dijkstra's type algorithm, it calculates the type of path of every
 * AS to a specified destination.
 *
 * @param network A pointer to the network with loaded data.
 * @param start The AS that serves as destination for the algorithm execution
 * @param option An optional flag which provides user to check more information
 * @return A pointer to an array of integers, which consists of the type of path from it index to destination.
 */

int *Commercial(const struct net *network, const int start, int option) {
    int *visitedLinkType = calloc(MAX, sizeof(int));
    int parent[MAX];

    for (int i = 0; i < MAX; i++) {
        parent[i] = -1;
    }
    printf("isCyclic %d\n", isCyclic);
    printf("isCo %d\n", isStronglyConnected);
    struct Node *list[3];
    list[0] = NULL, list[1] = NULL, list[2] = NULL;
    visitedLinkType[start] = -1; // Mark the start node as visited with link type -1
    parent[start] = -1; // Ver se vale a pena pois com os atalhos caminhos provider nao sao registados aqui!
    appendNode(list, start, visitedLinkType);

    while (list[2] || list[1] || list[0]) {
        const int currentVertex = removeNode(list);
        const struct link *temp = network->adj[currentVertex];
        while (temp) {
            const int adjV = temp->id;
            const int type = isValidRoute(visitedLinkType[currentVertex], temp->type);
            if (type != 1 || !isStronglyConnected) {
                if (type > visitedLinkType[adjV] && adjV != start) {
                    visitedLinkType[adjV] = type;
                    parent[adjV] = currentVertex;
                    if (type == 3 || !isStronglyConnected) {
                        appendNode(list, adjV, visitedLinkType);
                    }
                }
            }
            temp = temp->next;
        }
    }

    while (option != -1) {
    printf("Please select an AS to see more information (Enter -2 to see all) or (Enter -1 to leave):\n");
    if (fscanf(stdin, "%d", &option) != 1) {
        printf("Please input a number!\n");
    }

    if (option == -2) {
        // Iterate through all nodes in the network
        printf("\n");
        for (int i = 0; i < MAX; i++) {
            if (network->adj[i] != NULL) {
                printf("Information for node %d:\n", i);
                if (start == i) {
                    printf("The route from %d to %d is itself: %d\n", i, start, i);
                } else if (visitedLinkType[i] == 2) {
                    printf("There is a valid route from node %d to node %d (Peer-to-peer Path): ", i, start);
                    printPath(i, parent);
                    printf("\n");
                } else if (visitedLinkType[i] == 3) {
                    printf("There is a valid route from node %d to node %d (Customer Path): ", i, start);
                    printPath(i, parent);
                    printf("\n");
                } else if (visitedLinkType[i] == 1 || isStronglyConnected) {
                    printf("There is a valid route from node %d to node %d (Provider Path): ", i, start);
                    printPath(i, parent);
                    printf("\n");
                } else {
                    printf("There is not a valid route from node %d to node %d\n", i, start);
                }
                printf("\n");
            }
        }
    } else if (network->adj[option] != NULL) {
        printf("\n");
        if (start == option) {
            printf("The route from %d to %d is itself: %d\n", option, start, option);
        } else if (visitedLinkType[option] == 2) {
            printf("There is a valid route from node %d to node %d (Peer-to-peer Path): ", option, start);
            printPath(option, parent);
            printf("\n");
        } else if (visitedLinkType[option] == 3) {
            printf("There is a valid route from node %d to node %d (Customer Path): ", option, start);
            printPath(option, parent);
            printf("\n");
        } else if (visitedLinkType[option] == 1 || isStronglyConnected) {
            printf("There is a valid route from node %d to node %d (Provider Path): ", option, start);
            printPath(option, parent);
            printf("\n");
        } else {
            printf("There is not a valid route from node %d to node %d\n", option, start);
        }
        printf("\n");
    }
}

    return visitedLinkType; // Return the dynamically allocated array
}

/**
 * Inserts an element into a queue, depending on its visitedLinkType value.
 *
 * @param head A pointer to an array of lists, that serve as a priority queue.
 * @param vertex Vertex to be added to the queue, depending on it visited status.
 * @param visitedLinkType A pointer to an array of integers, which consists of the type of path from it index to destination.
 * @return void
 */

void appendNode(struct Node **head, int vertex, const int *visitedLinkType) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = vertex;
    newNode->next = NULL;
    printf("vou ligar o no %d a fila %d\n", vertex, visitedLinkType[vertex]);
    // If the node should be added at the head[1] position
    if (visitedLinkType[vertex] == -1) {
        newNode->next = head[2]; // Link the new node to the existing head[1]
        head[2] = newNode; // Update head[1] to point to the new node
    } else {
        newNode->next = head[visitedLinkType[vertex] - 1]; // Link the new node to the appropriate list
        head[visitedLinkType[vertex] - 1] = newNode; // Update head accordingly
    }
}

/**
 * Removes the first element of the queue.
 *
 * @param list A pointer to an array of lists, that serve as a priority queue.
 * @return Returns the first node on the queue, as an integer.
 */
int removeNode(struct Node **list) {
    for (int i = 2; i >= 0; i--) {
        if (list[i] != NULL) {
            struct Node *temp = list[i];
            const int AS = list[i]->data;
            list[i] = list[i]->next;
            free(temp);
            return AS;
        }
    }
    return -1; // Return -1 if no nodes are available to remove
}


/**
 * Using a Dijkstra's type algorithm, it calculates the type of path of every
 * AS to every other AS and gives statistics.
 *
 * @param network A pointer to the network with loaded data.
 * @return void
 */

void CommercialAll(const struct net *network) {
    long long totalPaths = 0, providerPaths = 0, customerPaths = 0, peerToPeerPaths = 0, invalidPaths = 0;
    int *visitedLinkType = NULL;

    for (int source = 0; source < MAX; source++) {
        if (network->adj[source] != NULL) {
            visitedLinkType = Commercial(network, source, -1);
            for (int destination = 0; destination < MAX; destination++) {
                if (network->adj[destination] != NULL) {
                    if (destination == source) continue;
                    if (visitedLinkType[destination] == 3) {
                        customerPaths++;
                    } else if (visitedLinkType[destination] == 2) {
                        peerToPeerPaths++;
                    } else if (visitedLinkType[destination] == 1) {
                        providerPaths++;
                    } else if (!isStronglyConnected) {
                        invalidPaths++;
                    }
                    totalPaths++;
                }
            }
            free(visitedLinkType);
        }
    }
    if (isStronglyConnected) {
        totalPaths = network->V * (network->V - 1);
        providerPaths = totalPaths - peerToPeerPaths - customerPaths;
    }

    printf("\nPath Type Probability Distribution:\n\n");
    printf("Total Paths: %lld | %.2lf%%\n", totalPaths, (double) totalPaths / totalPaths * 100);
    printf("Provider Paths: %lld | %.2lf%%\n", providerPaths, (double) providerPaths / totalPaths * 100);
    printf("Peer-to-Peer Paths: %lld | %.2lf%%\n", peerToPeerPaths, (double) peerToPeerPaths / totalPaths * 100);
    printf("Customer Paths: %lld | %.2lf%%\n", customerPaths, (double) customerPaths / totalPaths * 100);
    printf("Invalid Paths: %lld | %.2lf%%\n\n", invalidPaths, (double) invalidPaths / totalPaths * 100);
}

void printPath(int node, const int *parent) {
    // Use an array to store the path
    int path[MAX];
    int pathLength = 0;

    // Backtrack from node to target t using the parent array
    while (node != -1) {
        path[pathLength++] = node;
        node = parent[node]; // Move to the parent of the current node
    }

    // Print the path in reverse order (from node to target)
    for (int i = 0; i < pathLength; i++) {
        if (i > 0) printf(" -> ");
        printf("%d", path[i]);
    }
}
