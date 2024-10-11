#include <stdio.h>

#include "header.h"

bool isCyclic;
int index = 0;
int indices[MAX], lowLink[MAX], onStack[MAX], stack[MAX], stackTop = -1;
int sccCount = 0;
int sccId[MAX]; // To store which SCC each node belongs to


/**
 * Tells the user if the input network has cycles or not.
 *
 * @return void
 */
void CommercialCycle() {
    if (isCyclic) {
        printf("The network has at least a cycle in it!\n");
    } else {
        printf("The network does not have any cycle!\n");
    }
}

int isNodeInCycle[MAX]; // Array para marcar os nós que pertencem a ciclos


/**
 * This Tarjan's based algorithm finds the strongly connected components on a network.
 *
 * @param network A pointer to the network with loaded data.
 * @param v The AS that serves as destination for the algorithm execution.
 * @return void
 */
void findStronglyConnectedComponentsUtil(struct net *network, int v) {
    indices[v] = index;
    lowLink[v] = index;
    index++;
    stack[++stackTop] = v;
    onStack[v] = 1;

    const struct link *curr = network->adj[v];
    while (curr != NULL) {
        if (curr->type == 1) {
            if (indices[curr->id] == -1) {
                // Recur for unvisited nodes
                findStronglyConnectedComponentsUtil(network, curr->id);
                lowLink[v] = lowLink[v] < lowLink[curr->id] ? lowLink[v] : lowLink[curr->id];
            } else if (onStack[curr->id]) {
                // Update lowLink for back edges
                lowLink[v] = lowLink[v] < indices[curr->id] ? lowLink[v] : indices[curr->id];
            }
        }
        curr = curr->next;
    }

    // If v is the root of an SCC
    if (lowLink[v] == indices[v]) {
        int w, sccSize = 0;

        // Process the SCC and calculate its size
        do {
            w = stack[stackTop--];
            onStack[w] = 0;
            sccId[w] = sccCount;
            sccSize++;
        } while (w != v);

        // Only count the SCC if it has more than one node
        if (sccSize > 1) {
            sccCount++; // Increment SCC count only for cycles
        } else {
            // Reset the SCC ID for single-node SCC
            sccId[w] = -1;
        }
    }
}


/**
 * It sets the variables up in order to properly call the Tarjan's-like algorithm.
 *
 * @param network A pointer to the network with loaded data.
 *
 * @return void
 */

void findStronglyConnectedComponents(struct net *network) {
    isCyclic = 0;
    for (int i = 0; i < MAX; i++) {
        indices[i] = -1;
        lowLink[i] = -1;
        onStack[i] = 0;
        sccId[i] = -1;
        isNodeInCycle[i] = 0;
    }

    for (int i = 0; i < MAX; i++) {
        if (indices[i] == -1 && network->adj[i] != NULL) {
            findStronglyConnectedComponentsUtil(network, i);
        }
    }

    printf("tem %d ciclos\n", sccCount);
    printf("\n");

    if (isCyclic) {
        cycleRefactor(network);
    }
}

/**
 * Having known that there is at least a cycle in the netowrk, it converts any nodes that are in
 * a cycle to a supernode, to improve network navigation.
 *
 * @param network A pointer to the network with loaded data.
 * @return void
 */

void cycleRefactor(struct net *network) {
    for (int scc = 0; scc < sccCount; scc++) {
        // Create a super node for each SCC
        const int superNodeId = 65537 + scc; // Assuming super nodes have IDs greater than the original nodes

        // Add the super node to the network
        network->adj[superNodeId] = NULL;

        for (int i = 0; i < MAX; i++) {
            if (sccId[i] == scc) {
                // Redirect all edges out of the SCC to the super node
                const struct link *curr = network->adj[i];
                while (curr != NULL) {
                    if (sccId[curr->id] != scc) {
                        createEdge(network, superNodeId, curr->id, curr->type);
                    }
                    curr = curr->next;
                }
                // Remove the original node from the network
                network->adj[i] = NULL;
            }
        }

        // Redirect edges from other nodes into the super node
        for (int i = 0; i < MAX; i++) {
            if (sccId[i] != scc && network->adj[i] != NULL) {
                const struct link *curr = network->adj[i];
                while (curr != NULL) {
                    if (sccId[curr->id] == scc) {
                        createEdge(network, i, superNodeId, curr->type);
                        removeEdge(network, i, curr->id);
                    }
                    curr = curr->next;
                }
            }
        }
    }
}
