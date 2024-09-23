//

#include <stdio.h>
#include <stdlib.h>

#include "header.h"

void appendNode(struct Node** head, int vertex) {
    // Allocate memory for the new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    // Set the data (vertex) and point the new node to the current head
    newNode->data = vertex;
    newNode->next = *head;

    // Update the head to point to the new node
    *head = newNode;
}


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    *head = newNode;
}

void removeCurrentNode(struct Node** list, struct Node* previous, struct Node* current) {

    // Bypass the current node
    if (*list == current) {
        // If current is the head, update the head
        *list = (*list)->next;
    } else {
        // Otherwise, bypass the current node in the list
        previous->next = current->next;
    }

    // Free the current node
    free(current);
}


int removeTypeNode(struct net *network, struct Node** list, int *visitedLinkType){
    struct Node* current = *list;
    struct Node* previous = *list;
    struct Node* nodeV;
    struct Node* previousV;
    int vertice;
    int minType=-2;

    if (current == NULL) {
        return NULL;
    }

    // Traverse the linked list of the vertex
    while (current != NULL) {
        if (visitedLinkType[current->data]> minType) {
            minType = visitedLinkType[current->data];
            vertice= current->data;
            previousV=previous;
            nodeV=current;
        }
        previous=current;
        current = current->next;
    }
    removeCurrentNode(list,previousV,nodeV);
    return vertice;
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

int min_distance(long dist[], int visited[]) {
    long min = INF, min_index;

    for (int v = 0; v < MAX; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

int isValidRoute(const int prevType, const int currentType) {
    return prevType != -1 && (prevType <currentType || (prevType == 2 && currentType == 2));
}

void dijkstra_lenght(struct net *graph, int src) {
    long dist[MAX];     // Distance array to hold shortest distances from src
    int visited[MAX];  // Array to track visited vertices
    int type[MAX];    //tracks types

    // Initialize all distances to infinity and visited[] to false
    for (int i = 0; i < MAX; i++) {
        if(graph->adj[i]!=NULL){
            dist[i] = INF;
            visited[i] = 0;
        }else{
            visited[i] = -1;
        }
    }

    dist[src] = 0;
    type[src] = -1;

    // Process all vertices
    for (int count = 0; count < graph->V; count++) {
        int u = min_distance(dist, visited);
        visited[u] = 1;

        struct link *pCrawl = graph->adj[u];
        while (pCrawl != NULL) {
            int v = pCrawl->id;
            
            if(visited[v]  && !isValidRoute(type[u], pCrawl->type)){
                if(type[u]<type[v]){
                    dist[v] = dist[u] + 1;
                    type[v] = type[u];  
                }
            }
            
            if (!visited[v]  && !isValidRoute(type[u], pCrawl->type)) {
                dist[v] = dist[u] + 1;
                if(type[u]==-1){
                    type[v] = pCrawl->type;
                }else{
                    type[v]=type[u];
                }       
            }
            pCrawl = pCrawl->next;
        }
    }

    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < MAX; i++) {
        if(graph->adj[i]!=NULL){
            printf("%d \t\t %ld\n", i, dist[i]);
        }
        
    }

}


/*
void dijkstra_shortest_path(struct net *graph, int src) {
    long dist[MAX];     // Distance array to hold shortest distances from src
    int visited[MAX];  // Array to track visited vertices
    int type[MAX];    //tracks types

    // Initialize all distances to infinity and visited[] to false
    for (int i = 0; i < MAX; i++) {
        if(graph->adj[i]!=NULL){
            dist[i] = INF;
            visited[i] = 0;
        }else{
            visited[i] = -1;
        }
    }

    dist[src] = 0;
    type[src] = -1;

    // Process all vertices
    for (int count = 0; count < graph->V; count++) {
        int u = min_distance(dist, visited);
        visited[u] = 1;

        struct link *pCrawl = graph->adj[u];
        while (pCrawl != NULL) {
            int v = pCrawl->id;
            if (!visited[v] && dist[u] + 1 < dist[v] && !isInvalidRoute(type[u], pCrawl->type)) {
                dist[v] = dist[u] + 1;
                type[v] = type[u];
            }

            pCrawl = pCrawl->next;
        }
    }

    // Print the calculated shortest distances
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < MAX; i++) {
        if(graph->adj[i]!=NULL){
            printf("%d \t\t %ld\n", i, dist[i]);
        }
        
    }
}
*/
void CommercialLengths(struct net *net, int t) {

  
    dijkstra_lenght(net, t);

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

int isInvalidRoute(const int prevType, const int currentType) {
    return prevType != -1 && (prevType < currentType || (prevType == 2 && currentType == 2));
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
            if (!isInvalidRoute(prevType, curr->type)) {
                // Provider or Customer
                dfs(network, curr->id, curr->type, visitedLinkType);
            }
        }
        curr = curr->next;
    }
}


void bfs(struct net *network, int node, int *visitedLinkType) {

    struct Node* list = NULL;     // List to hold vertices to be visited

    // Start BFS from the starting vertex
    visitedLinkType[node] = -1;
    insertAtBeginning(&list, node);

    while (list != NULL) {
        // Remove the first vertex from the list
        int currentVertex = removeTypeNode(network, &list, visitedLinkType);

        // Explore all the adjacent vertices
        struct link* temp = network->adj[currentVertex];
        while (temp) {
            int adjV = temp->id;
            if(!isInvalidRoute(visitedLinkType[currentVertex],temp->type)){
                if (!visitedLinkType[adjV]) {
                    visitedLinkType[adjV] = temp->type;
                    appendNode(&list, adjV);
                }else if(temp->type> visitedLinkType[adjV] && adjV!=node){
                    visitedLinkType[adjV]=temp->type;
                }
            }
            temp = temp->next;
        }
    }
}


int canAllReachTarget(struct net *network, int t) {
    int visitedLinkType[MAX] = {0};
    bfs(network, t, visitedLinkType);

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
