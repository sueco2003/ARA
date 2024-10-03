//

#include <stdio.h>
#include <stdlib.h>

#include "header.h"

void appendNode(struct Node **head, int vertex, const int *visitedLinkType) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = vertex;
    newNode->next = NULL;
    // If the node should be added at the head[1] position
    if (visitedLinkType[vertex] == -1) {
        newNode->next = head[1]; // Link the new node to the existing head[1]
        head[1] = newNode; // Update head[1] to point to the new node
    } else {
        newNode->next = head[visitedLinkType[vertex] - 1]; // Link the new node to the appropriate list
        head[visitedLinkType[vertex] - 1] = newNode; // Update head accordingly
    }
}

int removeNode(struct Node **list) {
    for (int i = 0; i < 3; i++) {
        // Loop through the lists
        if (list[i] != NULL) {
            struct Node *temp = list[i];
            int AS = list[i]->data;
            list[i] = list[i]->next;
            free(temp);
            return AS;
        }
    }
    return -1; // Return -1 if no nodes are available to remove
}

int isCyclicUtil(struct net *network, int node, int *visited, int *recStack) {
    // Mark the current node as visited and add it to the recursion stack
    visited[node] = 1;
    recStack[node] = 1;

    const struct link *curr = network->adj[node];

    while (curr != NULL) {
        if (curr->type == 3) {
            // Only process nodes of type 3 (or any logic you want)
            // If the node hasn't been visited, recurse on it
            if (!visited[curr->id]) {
                if (isCyclicUtil(network, curr->id, visited, recStack)) {
                    return 1; // Cycle detected
                }
            } else if (recStack[curr->id]) {
                // Cycle detected, print the recursion stack
                printf("Cycle detected! Recursion stack: ");
                for (int i = 0, count = 0; i < MAX; i++) {
                    if (recStack[i]) {
                        if (count) printf(" -> ");
                        count++;
                        printf("%d", i);
                    }
                }
                printf("\n");
                return 1; // Return to indicate a cycle was found
            }
        }
        curr = curr->next; // Move to the next adjacent node
    }

    // Remove the node from the recursion stack
    recStack[node] = 0;
    return 0;
}

int isCyclic(struct net *net) {
    const int V = MAX;
    int visited[V];
    int recStack[V];

    // Initialize visited and recursion stack arrays
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        recStack[i] = 0;
    }

    // Call the utility function for all unvisited nodes
    for (int i = 0; i < V; i++) {
        if (!visited[i] && net->adj[i] != NULL) {
            if (isCyclicUtil(net, i, visited, recStack)) {
                return 1; // Cycle detected
            }
        }
    }
    return 0; // No cycle found
}

int *Commercial(const struct net *network, const int t, int option) {
    // Dynamically allocate memory for visitedLinkType
    int *visitedLinkType = (int *) malloc(MAX * sizeof(int));
    if (visitedLinkType == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed!\n");
        return NULL;
    }

    int parent[MAX]; // Tracks the parent of each node during BFS

    // Initialize parent array with -1 (indicating no predecessor)
    for (int i = 0; i < MAX; i++) {
        visitedLinkType[i] = 0; // Initialize visitedLinkType to 0
        parent[i] = -1; // Initialize parent array to -1
    }

    int count = 0;
    struct Node *list[3];
    list[0] = NULL;
    list[1] = NULL;
    list[2] = NULL;

    // Start BFS from the starting vertex
    visitedLinkType[t] = -1; // Mark the start node as visited with link type -1
    parent[t] = -1; // The starting node has no predecessor
    appendNode(list, t, visitedLinkType);
    count++;

    while (count) {
        // Remove the first vertex from the list (or the best vertex)
        const int currentVertex = removeNode(list);
        count--;

        // Explore all the adjacent vertices
        const struct link *temp = network->adj[currentVertex];
        while (temp) {
            const int adjV = temp->id;
            if (isValidRoute(visitedLinkType[currentVertex], temp->type)) {
                if (!visitedLinkType[adjV]) {
                    // If the vertex hasn't been visited, visit it
                    visitedLinkType[adjV] = temp->type;
                    parent[adjV] = currentVertex; // Track where we came from
                    appendNode(list, adjV, visitedLinkType); // Add this node to the list
                    count++;
                } else if (temp->type > visitedLinkType[adjV] && adjV != t) {
                    // If we find a better link, update the link type and the predecessor
                    visitedLinkType[adjV] = temp->type;
                    parent[adjV] = currentVertex; // Update where we came from
                }
            }
            temp = temp->next;
        }
    }

    // Handle user input and output paths
    while (option != -1) {
        printf("Please select an AS to see more information (Enter -1 to leave):\n");
        if (fscanf(stdin, "%d", &option) != 1) {
            printf("Please input a number!\n");
        }
        if (network->adj[option] != NULL) {
            // Check only nodes that exist in the graph
            if (visitedLinkType[option] == 1) {
                printf("There is a valid route from node %d to node %d (Provider Path): ", option, t);
                printPath(option, parent);
                printf("\n");
            } else if (visitedLinkType[option] == 2) {
                printf("There is a valid route from node %d to node %d (Peer-to-peer Path): ", option, t);
                printPath(option, parent);
                printf("\n");
            } else if (visitedLinkType[option] == 3) {
                printf("There is a valid route from node %d to node %d (Customer Path): ", option, t);
                printPath(option, parent);
                printf("\n");
            } else if (t == option) {
                printf("The route from %d to %d is itself: %d\n", option, t, option);
            } else {
                printf("There is not a valid route from node %d to node %d\n", option, t);
            }
            printf("\n");
        }
    }
    return visitedLinkType; // Return the dynamically allocated array
}


void CommercialTest(struct net *net, int s, int t) {
}

int CommercialCycle(struct net *net) {
    if (isCyclic(net)) {
        printf("There is at least one cycle in this network\n");
        return 1;
    } else {
        printf("There isn't a cycle in this network\n");
        return 0;
    }
}

void CommercialAll(struct net *net) {
    long totalPaths = 0, providerPaths = 0, customerPaths = 0, peerToPeerPaths = 0;
    int *visitedLinkType = calloc(MAX, sizeof(int)); // Initial allocation for visitedLinkType

    if (CommercialCycle(net) || !CommercialConnected(net)) {
        int invalidPaths = 0;
        // Iterate over all AS nodes in the network
        for (int origin = 0; origin < MAX; origin++) {
            if (net->adj[origin]) {
                int *newVisitedLinkType = Commercial(net, origin, -1); // Call Commercial and get the new array

                if (visitedLinkType != NULL) {
                    free(visitedLinkType); // Free the previous memory to prevent memory leak
                }

                visitedLinkType = newVisitedLinkType; // Assign the newly allocated array to visitedLinkType
            }

            for (int i = 0; i < MAX; i++) {
                if (net->adj[i]) {
                    if (visitedLinkType[i] == 1) {
                        providerPaths++;
                    } else if (visitedLinkType[i] == 2) {
                        peerToPeerPaths++;
                    } else if (visitedLinkType[i] == 3) {
                        customerPaths++;
                    } else {
                        invalidPaths++;
                    }
                    totalPaths++;
                }
            }
        }
        if (visitedLinkType != NULL) {
            free(visitedLinkType); // Free at the end to avoid memory leak
        }
    } else {
        for (int origin = 0; origin < MAX; origin++) {
            dfs(net, origin, -1, visitedLinkType);
            for (int peer = 0; peer < MAX; peer++) {
                if (net->adj[peer]) {
                    if (visitedLinkType[peer] == 1) {
                        providerPaths++;
                    } else if (visitedLinkType[peer] == 2) {
                        peerToPeerPaths++;
                    } else if (!visitedLinkType[peer]) {
                        customerPaths++;
                    }
                    totalPaths++;
                }
            }
        }

        printf("\nPath Type Probability Distribution:\n");
        if (totalPaths > 0) {
            printf("Provider Paths: %.2f%%\n", (float) providerPaths / totalPaths * 100);
            printf("Peer-to-Peer Paths: %.2f%%\n", (float) peerToPeerPaths / totalPaths * 100);
            printf("Customer Paths: %.2f%%\n", (float) customerPaths / totalPaths * 100);
        } else {
            printf("No paths found.\n");
        }
    }
}


int CommercialConnected(struct net *net) {
    int tier1 = 0, start = -1, i;
    int prev = -1;

    for (i = 0; i < MAX; i++) {
        if (net->adj[i] != NULL) {
            int valid = 1;
            const struct link *temp = net->adj[i];
            while (temp != NULL) {
                if (temp->type == 3) {
                    valid = 0;
                    break;
                }
                temp = temp->next;
            }
            if (valid) {
                tier1++;
                start = i;
            }
        }
    }
    int current = start;
    while (tier1) {
        const struct link *temp = net->adj[current];
        int changed = 0;
        while (temp != NULL) {
            if (temp->type == 2 && temp->id != prev) {
                tier1--;
                prev = current;
                current = temp->id;
                changed = 1;
                temp = NULL;
                continue;
            }
            temp = temp->next;
        }
        if (!changed) {
            printf("The net is not strongly connected!\n");
            return 0;
        }
    }
    printf("The net is strongly connected!\n");
    return 1;
}


int isValidRoute(const int prevType, const int currentType) {
    return prevType == -1 || prevType == 3 || currentType == 1;
}

void CommercialLengths(struct net *net, int t) {
}

void CommercialLengthsAll(struct net *net) {
}

void ShortestAll(struct net *net) {
}

void dfs(struct net *network, int node, int prevType, int *visitedLinkType) {
    if (visitedLinkType[node] != 0) {
        return; // Node already visited
    }

    visitedLinkType[node] = prevType; // Mark node as visited
    struct link *curr = network->adj[node];

    while (curr != NULL) {
        // Perform type-checking rules here:
        if (visitedLinkType[curr->id] == 0) {
            // Unvisited node
            if (isValidRoute(prevType, curr->type) && curr->type != -1) {
                // Provider or Customer
                dfs(network, curr->id, curr->type, visitedLinkType);
            }
        }
        curr = curr->next;
    }
}

void printPath(int node, int *parent) {
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
