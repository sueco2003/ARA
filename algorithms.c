//

#include <stdio.h>
#include <stdlib.h>

#include "header.h"

struct MinHeap {
    int *array;   // Array to store the heap
    int capacity; // Maximum possible size of the heap
    int size;     // Current size of the heap
};

// Function to create a new min-heap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (int*)malloc(capacity * sizeof(int));
    return minHeap;
}

// Function to get the index of the parent of a node
int parent(int i) { return (i - 1) / 2; }

// Function to get the index of the left child of a node
int left(int i) { return (2 * i + 1); }

// Function to get the index of the right child of a node
int right(int i) { return (2 * i + 2); }

// Function to swap two elements
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Function to heapify (bubble down) a subtree with root at index i
void heapify(struct MinHeap* minHeap, int i) {
    int smallest = i;      // Initialize smallest as root
    int l = left(i);       // Left child
    int r = right(i);      // Right child

    // Check if the left child is smaller than the root
    if (l < minHeap->size && minHeap->array[l] < minHeap->array[smallest])
        smallest = l;

    // Check if the right child is smaller than the smallest so far
    if (r < minHeap->size && minHeap->array[r] < minHeap->array[smallest])
        smallest = r;

    // If the smallest is not the root, swap and continue heapifying
    if (smallest != i) {
        swap(&minHeap->array[i], &minHeap->array[smallest]);
        heapify(minHeap, smallest);
    }
}

// Function to extract the minimum element from the heap
int extractMin(struct MinHeap* minHeap) {
    if (minHeap->size <= 0)
        return MAX;
    if (minHeap->size == 1) {
        minHeap->size--;
        return minHeap->array[0];
    }

    // Store the minimum value and remove it from the heap
    int root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;

    // Restore the heap property by heapifying
    heapify(minHeap, 0);

    return root;
}

// Function to insert a new key into the heap
void insertKey(struct MinHeap* minHeap, int key) {
    if (minHeap->size == minHeap->capacity) {
        printf("Overflow: Could not insert key\n");
        return;
    }

    // Insert the new key at the end
    int i = minHeap->size;
    minHeap->array[i] = key;
    minHeap->size++;

    // Fix the min-heap property by "bubbling up"
    while (i != 0 && minHeap->array[parent(i)] > minHeap->array[i]) {
        swap(&minHeap->array[i], &minHeap->array[parent(i)]);
        i = parent(i);
    }
}






int isInvalidRoute(const int prevType, const int currentType) {
    return prevType != -1 && (prevType < currentType || (prevType == 2 && currentType == 2));
}

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
        return -1;
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






bool removeTypeDistanceNode(struct net *network, struct Node** list, long *dist, int *currentVertex){
    struct Node* current = *list;
    struct Node* previous = *list;
    struct Node* nodeV;
    struct Node* previousV;
    int vertice;
    int minType=-2;

    if (current == NULL) {
        return false;
    }

    // Traverse the linked list of the vertex
    while (current != NULL) {
        if (dist[current->data]> minType) {
            minType = dist[current->data];
            vertice= current->data;
            previousV=previous;
            nodeV=current;
        }
        previous=current;
        current = current->next;
    }
    removeCurrentNode(list,previousV,nodeV);
    (*currentVertex)=vertice;
    return true;
}

void dijkstra_lenght(struct net *graph, int src, long *dist, int *prev) {
        
    int type[MAX];    //tracks types

    struct Node* list_type1 = NULL;
    struct Node* list_type2 = NULL;
    struct Node* list_type3 = NULL;

    // Initialize all distances to infinity and visited[] to false
    for (int i = 0; i < MAX; i++) {
        if(graph->adj[i]!=NULL){
            dist[i] = INF;
            type[i] = 0;
            prev[i] =-1;
        }
    }
    dist[src] = 0;
    type[src] = -1;
    appendNode(&list_type3,src);
    int currentVertex;

    while (list_type3 != NULL || list_type2!=NULL || list_type1!=NULL) {
        // Remove the first vertex from the list
        if(!removeTypeDistanceNode(graph, &list_type3, dist, &currentVertex)){
            if(!removeTypeDistanceNode(graph, &list_type2, dist, &currentVertex)){
                removeTypeDistanceNode(graph, &list_type1, dist, &currentVertex);
            }
        }
        // Explore all the adjacent vertices
        struct link* temp = graph->adj[currentVertex];
        while (temp) {
            int adjV = temp->id;
            if(!isInvalidRoute(type[currentVertex],temp->type)){
                if (temp->type>type[adjV] && type[adjV]!=-1) {
                    type[adjV] = temp->type;
                    dist[adjV] = dist[currentVertex] +1;
                    prev[adjV]= currentVertex;
                    
                    switch (temp->type)
                    {
                    case 1:
                        appendNode(&list_type1,adjV);
                        break;
                    case 2:
                        appendNode(&list_type2,adjV);
                        break;
                    case 3:
                        appendNode(&list_type3,adjV);
                        break;
                    
                    default:
                        break;
                    }
                }else if(temp->type==type[adjV] && dist[adjV]>dist[currentVertex]+1){
                    dist[adjV]=dist[currentVertex]+1;
                    prev[adjV]= currentVertex;
                }
            }
            temp = temp->next;
        }
    }

}



void CommercialLengths(struct net *net, int t) {

    long dist[MAX];
    int prev[MAX];
    dijkstra_lenght(net, t, dist, prev);
    printf("Vertex   Distance from Source    Path\n");
    for (int i = 0; i < MAX; i++) {
        if(net->adj[i]!=NULL){
            if(dist[i]==INF){
                printf("%d \t\t Invalid \n", i);
            }else{
                printf("%d \t\t %ld \t\t ", i, dist[i]);
                int node=i;
                printf("%d", node);
                while(prev[node]!=-1){
                    node=prev[node];
                    printf("-%d", node);
                }
                printf("\n");
            }
            
        }
        
    }

}

void CommercialLengthsTest(struct net *net, int t) {

    long dist[MAX];
    int prev[MAX];
    dijkstra_lenght(net, t, dist, prev);

    int s=0;
    while(1){
        printf("Please insert the source AS or -1 to exit:\n");
        if (fscanf(stdin, "%d", &s) != 1) {
            printf("Please provide the input needed!\n");
        }else{
            if(s==-1){
                break;
            }
            printf("Vertex   Distance from Source    Path\n");
            if(dist[s]==INF){
                printf("%d \t\t Invalid \n", s);
            }else{
                printf("%d \t\t %ld \t\t ", s, dist[s]);
                int node=s;
                printf("%d", node);
                while(prev[node]!=-1){
                    node=prev[node];
                    printf("-%d", node);
                }
                printf("\n");
            }
        }
    }

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
