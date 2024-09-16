//

#include <stdio.h>
#include <stdlib.h>

#include "header.h"

int isCyclicUtil(struct net* network, int node, int* visited, int* recStack) {
    // Mark the current node as visited and add it to the recursion stack
    visited[node] = 1;
    recStack[node] = 1;

    const struct link* curr = network->adj[node];

    while (curr != NULL) {
        if (curr->type == 3) {  // Only process nodes of type 3 (or any logic you want)
            // If the node hasn't been visited, recurse on it
            if (!visited[curr->id]) {
                if (isCyclicUtil(network, curr->id, visited, recStack)) {
                    return 1;  // Cycle detected
                }
            } else if (recStack[curr->id]) {
                return 1;  // Cycle detected (if it's already in recursion stack)
            }
        }
        curr = curr->next;  // Move to the next adjacent node
    }

    // Remove the node from the recursion stack
    recStack[node] = 0;
    return 0;
}

// Function to detect a cycle in the graph
int isCyclic(struct net* net) {
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
                return 1;  // Cycle detected
            }
        }
    }
    return 0;  // No cycle found
}


void Commercial(struct net *net, int t) {
    canAllReachTarget(net, t);
}

void CommercialTest(struct net *net, int s, int t) {
}

void CommercialCycle(struct net *net) {
    /*int visitedLinkType[MAX] = {0};
    int t = 0;
    int cycle = 0;
    for (int i = 0; i < MAX; i++) {
        if (net->adj[i] != NULL) {
            t = i;
            break;
        }
    }
    cycle = dfs_cycle(net, t, -1, visitedLinkType);
    if (cycle == 1) {
        printf("There is at least one cycle in this network\n");
    } else {
        printf("There isn't a cycle in this network\n");
    }*/

    if (isCyclic(net)) {
        printf("There is at least one cycle in this network\n");
    } else {
        printf("There isn't a cycle in this network\n");
    }
}

    void CommercialConnected(struct net *net) {
    }

    void CommercialLengths(struct net *net, int t) {
    }

    void CommercialLengthsAll(struct net *net) {
    }

    void ShortestAll(struct net *net) {
    }

    // Option 1: Find a path from any node to the destination node
    /*
    void findPathFromAnyNode(struct net *net, int t) {
        int visited[MAX] = {0}; // Initialize visited array
        // Try starting from every node in the graph
        for (int i = 0; i < MAX; i++) {
            if (net->adj[i]->active) {
                printf("id: %d\n", i);
                // Call DFS for every node, considering it as a potential start node
                int dfsResult = DFS(net, i, -1, t, visited);
                if (dfsResult == 1) {
                    printf("There is a valid route from node %d to node %d (Provider Path)\n", i, t);
                } else if (dfsResult == 2) {
                    printf("There is a valid route from node %d to node %d (Peer-to-peer Path)\n", i, t);
                } else if (dfsResult == 3) {
                    printf("There is a valid route from node %d to node %d Customer Path)\n", i, t);
                } else {
                    printf("There is not a valid route from node %d to node %d\n", i, t);
                }
                memset(visited, 0, sizeof(visited));
            }
        }
    }
    */


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
                if (isValidRoute(prevType, curr->type)) {
                    // Provider or Customer
                    dfs(network, curr->id, curr->type, visitedLinkType);
                }
            }
            curr = curr->next;
        }
    }

    int canAllReachTarget(struct net *network, int t) {
        int visitedLinkType[MAX] = {0};
        dfs(network, t, -1, visitedLinkType);

        for (int i = 0; i < MAX; i++) {
            if (network->adj[i] != NULL) {
                if (visitedLinkType[i] == 1) {
                    printf("There is a valid route from node %d to node %d (Provider Path)\n", i, t);
                } else if (visitedLinkType[i] == 2) {
                    printf("There is a valid route from node %d to node %d (Peer-to-peer Path)\n", i, t);
                } else if (visitedLinkType[i] == 3) {
                    printf("There is a valid route from node %d to node %d (Customer Path)\n", i, t);
                } else if (t == i) {
                    printf("The route from %d to %d is itself\n", i, t);
                } else {
                    printf("There is not a valid route from node %d to node %d\n", i, t);
                }
            }
        }
        printf("\n\n");
        return EXIT_SUCCESS;
    }

    int isValidRoute(const int prevType, const int currentType) {
        return prevType == -1 || prevType >= currentType ? prevType : 0;
    }
