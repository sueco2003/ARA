//

#include <stdio.h>
#include <stdlib.h>

#include "header.h"

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
                return 1; // Cycle detected (if it's already in recursion stack)
            }
        }
        curr = curr->next; // Move to the next adjacent node
    }

    // Remove the node from the recursion stack
    recStack[node] = 0;
    return 0;
}

// Function to detect a cycle in the graph
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
    kosaraju(net);
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
            if (!isInvalidRoute(prevType, curr->type)) {
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

int isInvalidRoute(const int prevType, const int currentType) {
    return prevType != -1 && (prevType < currentType || (prevType == 2 && currentType == 2));
}

void dfsOriginal(struct net *graph, int v, bool visited[], int *stack, int *stackIndex, int prevType) {
    visited[v] = true;
    printf("Visitei o %d\n", v);
    struct link *curr = graph->adj[v];
    while (curr != NULL) {
        if (!visited[curr->id]) {
            if (!isInvalidRoute(prevType, curr->type)) {
                dfsOriginal(graph, curr->id, visited, stack, stackIndex, curr->type);
            }
        }
        curr = curr->next;
    }

    stack[(*stackIndex)++] = v; // Store finishing time
}

// Function to transpose the graph
void transposeGraph(struct net *graph, struct net *transposed) {
    int reversedType;
    for (int i = 0; i < MAX; i++) {
        transposed->adj[i] = NULL;
    }

    for (int v = 0; v < MAX; v++) {
        struct link *temp = graph->adj[v];
        while (temp != NULL) {
            if (temp->type == 2) {
                reversedType = temp->type;
            } else if (temp->type == 1) {
                reversedType = 3;
            } else {
                reversedType = 1;
            }
            createEdge(transposed, temp->id, v, reversedType); // Reverse the direction but keep the type
            temp = temp->next;
        }
    }
}

// DFS for the transposed graph to find strongly connected components
void dfsTransposed(struct net *graph, int v, bool visited[], int prevType) {
    visited[v] = true;
    printf("%d ", v); // Print the strongly connected component

    struct link *temp = graph->adj[v];
    while (temp != NULL) {
        if (!visited[temp->id]) {
            printf("%d %d\n", prevType, temp->type);
            if (!isInvalidRoute(prevType, temp->type)) {
                printf("entrou");
                dfsTransposed(graph, temp->id, visited, temp->type);
            }
        }
        temp = temp->next;
    }
}

// Kosaraju's algorithm to find and print all SCCs
void kosaraju(struct net *graph) {
    int stack[MAX];
    int stackIndex = 0;
    bool visited[MAX] = {false};

    // Step 1: Do DFS on the original graph and store the nodes by their finishing times
    for (int i = 0; i < MAX; i++) {
        if (!visited[i] && graph->adj[i] != NULL) {
            dfsOriginal(graph, i, visited, stack, &stackIndex, -1);
        }
    }

    // Step 2: Transpose the graph
    struct net transposed;
    transposeGraph(graph, &transposed);

    // Step 3: Do DFS on the transposed graph in the order of decreasing finishing times
    for (int i = 0; i < MAX; i++) {
        visited[i] = false; // Reset visited array
    }

    int sccCount = 0;
    for (int i = stackIndex - 1; i >= 0; i--) {
        int v = stack[i];
        if (!visited[v]) {
            printf("SCC: ");
            dfsTransposed(&transposed, v, visited, -1);
            printf("\n");
            sccCount++;
        }
    }

    // Step 4: Check if the graph is strongly connected
    if (sccCount == 1) {
        printf("The graph is strongly connected.\n");
    } else {
        printf("The graph is not strongly connected.\n");
    }
}
