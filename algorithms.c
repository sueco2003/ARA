//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

int dfs_cycle(struct net *network, int node, int prevNode, int *visitedLinkType) {
    int cycle=0;
    visitedLinkType[node] = 1; // Mark node as visited
    struct link *curr = network->adj[node];

    while (curr != NULL) {
        if (visitedLinkType[curr->id] == 0) {
            // Unvisited node
            cycle=dfs_cycle(network, curr->id, node, visitedLinkType);
            if (cycle==1) {
                return 1;  // A valid commercial cycle has been found
            }
        }else if(visitedLinkType[curr->id] == 1 && prevNode!=curr->id){
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}




void Commercial(struct net *net, int t) {
    canAllReachTarget(net, t);  
}

void CommercialTest(struct net *net, int s, int t){
    
}

void CommercialCycle(struct net *net) {

    int visitedLinkType[MAX] = {0};
    int t=0;
    int cycle=0;
    for(int i=0;i<MAX;i++){
        if(net->adj[i]!=NULL){
            t=i;
            break;
        }
    }
    cycle=dfs_cycle(net, t, -1, visitedLinkType);
    if(cycle==1){
        printf("There is at least one cycle in this network\n");
    }else{
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
        if (network->adj[i]!=NULL) {
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

int isValidRoute(int prevType, int currentType) {
    return prevType == -1 || (prevType >= currentType) ? prevType : 0;
}