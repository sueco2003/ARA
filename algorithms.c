//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

struct MinHeapNode {
    int node;      // The node number
    int distance;  // The distance value
};

// Define the MinHeap structure with a static array
struct MinHeap {
    struct MinHeapNode array[MAX];  // Static array to store the heap
    int size;                       // Current size of the heap
    int position[MAX];              // To store the index of each node in the heap
};

// Function to initialize the heap
void initializeMinHeap(struct MinHeap* minHeap) {
    minHeap->size = 0;
    for (int i = 0; i < MAX; i++) {
        minHeap->position[i] = -1;  // Initially, no node is in the heap
    }
}

// Function to get the index of the parent of a node
int parent(int i) { return (i - 1) / 2; }

// Function to get the index of the left child of a node
int left(int i) { return (2 * i + 1); }

// Function to get the index of the right child of a node
int right(int i) { return (2 * i + 2); }

// Function to swap nodes in the heap and update their positions
void swapNodes(struct MinHeap* minHeap, int idx1, int idx2) {
    struct MinHeapNode temp = minHeap->array[idx1];
    minHeap->array[idx1] = minHeap->array[idx2];
    minHeap->array[idx2] = temp;

    // Update the positions of the nodes
    minHeap->position[minHeap->array[idx1].node] = idx1;
    minHeap->position[minHeap->array[idx2].node] = idx2;
}

// Function to heapify (bubble down) a subtree with root at index i
void heapify(struct MinHeap* minHeap, int i) {
    int smallest = i;      // Initialize smallest as root
    int l = left(i);       // Left child
    int r = right(i);      // Right child

    // Check if the left child is smaller than the root based on distance
    if (l < minHeap->size && minHeap->array[l].distance < minHeap->array[smallest].distance)
        smallest = l;

    // Check if the right child is smaller than the smallest so far
    if (r < minHeap->size && minHeap->array[r].distance < minHeap->array[smallest].distance)
        smallest = r;

    // If the smallest is not the root, swap and continue heapifying
    if (smallest != i) {
        swapNodes(minHeap, i, smallest);
        heapify(minHeap, smallest);
    }
}

// Function to bubble up (fix the min-heap property upwards)
void bubbleUp(struct MinHeap* minHeap, int i) {
    while (i != 0 && minHeap->array[parent(i)].distance > minHeap->array[i].distance) {
        swapNodes(minHeap, i, parent(i));
        i = parent(i);
    }
}

// Function to extract the node with the minimum distance from the heap
bool extractMin(struct MinHeap* minHeap, int *currentV) {
    if (minHeap->size <= 0) {
        // Return a dummy node with maximum distance if heap is empty
        
        return false;
    }

    if (minHeap->size == 1) {
        minHeap->size--;
        (*currentV)=minHeap->array[0].node;
        return true;
    }

    // Store the minimum value and remove it from the heap
    struct MinHeapNode root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->position[minHeap->array[0].node] = 0;  // Update the position of the last node
    minHeap->size--;

    // Restore the heap property by heapifying
    heapify(minHeap, 0);

    (*currentV)= root.node;
    return true;
}

// Function to insert a new node and distance into the heap
void insertKey(struct MinHeap* minHeap, int node, int distance) {
    if (minHeap->size == MAX) {
        printf("Overflow: Could not insert key\n");
        return;
    }

    // Insert the new node and distance at the end
    int i = minHeap->size;
    minHeap->array[i].node = node;
    minHeap->array[i].distance = distance;
    minHeap->position[node] = i;  // Track the position of this node in the heap
    minHeap->size++;

    // Fix the min-heap property by "bubbling up"
    bubbleUp(minHeap, i);
}

// Function to decrease the distance of a node in the heap
void decreaseKey(struct MinHeap* minHeap, int node, int newDistance) {
    int i = minHeap->position[node];  // Get the index of the node in the heap

    // If the new distance is greater, it's not a decrease-key operation
    if (newDistance > minHeap->array[i].distance) {
        printf("New distance is greater than the current distance\n");
        return;
    }

    // Update the distance
    minHeap->array[i].distance = newDistance;

    // Fix the min-heap property by "bubbling up"
    bubbleUp(minHeap, i);
}

// Function to update the distance of a node (either increase or decrease)
void updateKey(struct MinHeap* minHeap, int node, int newDistance) {
    int i = minHeap->position[node];  // Get the index of the node in the heap

    int currentDistance = minHeap->array[i].distance;

    // If the new distance is smaller, bubble up
    if (newDistance < currentDistance) {
        decreaseKey(minHeap, node, newDistance);
    }
    // If the new distance is larger, bubble down
    else if (newDistance > currentDistance) {
        minHeap->array[i].distance = newDistance;
        heapify(minHeap, i);  // Fix the heap by bubbling down
    }
}

void deleteNode(struct MinHeap* minHeap, int node) {
    // Get the index of the node to be deleted
    int i = minHeap->position[node];

    // If the node is not in the heap, return
    if (i == -1) {
        printf("Node not found in the heap\n");
        return;
    }

    // Replace the node with the last node in the heap
    minHeap->array[i] = minHeap->array[minHeap->size - 1];
    minHeap->position[minHeap->array[i].node] = i; // Update the position of the last node
    minHeap->size--;  // Reduce the size of the heap

    // Update the position array to indicate that the node is no longer in the heap
    minHeap->position[node] = -1;

    // Restore the heap property by either bubbling up or down
    if (i > 0 && minHeap->array[i].distance < minHeap->array[parent(i)].distance) {
        bubbleUp(minHeap, i);
    } else {
        heapify(minHeap, i);
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



int removeNode(struct net *network, struct Node** list, int node){
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
        if (node== current->data) {
            minType = node;
            vertice= current->data;
            previousV=previous;
            nodeV=current;
            break;
        }
        previous=current;
        current = current->next;
    }
    removeCurrentNode(list,previousV,nodeV);
    return NULL;
}


bool removeTypeDistanceNode(struct net *network, struct Node** list, int *dist, int *currentVertex){
    struct Node* current = *list;
    struct Node* previous = *list;
    struct Node* nodeV;
    struct Node* previousV;
    int vertice;
    int minType=INF;

    if (current == NULL) {
        return false;
    }

    // Traverse the linked list of the vertex
    while (current != NULL) {
        if (dist[current->data]< minType) {
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





void dijkstra_lenght(struct net *graph, int src, int *dist, int *prev) {
        
    int type[MAX]; 
    int processed[MAX];   

    struct MinHeap list_type1; 
    struct MinHeap list_type2; 
    struct MinHeap list_type3; 

    initializeMinHeap(&list_type1);
    initializeMinHeap(&list_type2);
    initializeMinHeap(&list_type3);

    for (int i = 0; i < MAX; i++) {
        if(graph->adj[i]!=NULL){
            dist[i] = INF;
            type[i] = 0;
            prev[i] =-1;
            processed[i]=-1;
        }
    }
    dist[src] = 0;
    type[src] = -1;
    insertKey(&list_type3, src, 0);
    int currentVertex;

    while (list_type3.size != 0 || list_type2.size!=0 || list_type1.size!=0) {
        // Remove the first vertex from the list
        if(!extractMin(&list_type3,&currentVertex)){
            if(!extractMin(&list_type2,&currentVertex)){
                extractMin(&list_type1,&currentVertex);
            }
        }
        // Explore all the adjacent vertices
        struct link* temp = graph->adj[currentVertex];
        if(processed[currentVertex]==1){
            continue;
        }
        while (temp) {
            int adjV = temp->id;
            if(prev[currentVertex]==adjV){
                temp = temp->next;
                continue;
            }
            if(!isInvalidRoute(type[currentVertex],temp->type)){
                if (temp->type>type[adjV] && type[adjV]!=-1) {
                    
                    if(type[adjV]!=0){
                        switch (type[adjV])
                        {
                        case 1:
                            deleteNode(&list_type1, adjV);
                            break;
                        case 2:
                            deleteNode(&list_type2, adjV);
                            break;
                        case 3:
                            deleteNode(&list_type3, adjV);
                            break;
                        default:
                            break;
                        }
                    }

                    type[adjV] = temp->type;
                    dist[adjV] = dist[currentVertex] +1;
                    prev[adjV]= currentVertex;
                    
                    switch (temp->type)
                    {
                    case 3:
                        insertKey(&list_type3, adjV, dist[adjV]);
                        break;
                    case 2:
                        insertKey(&list_type2, adjV, dist[adjV]);
                        break;
                    case 1:
                        insertKey(&list_type1, adjV, dist[adjV]);
                        break;
                    
                    default:
                        break;
                    }
                }else if(temp->type==type[adjV] && dist[adjV]>dist[currentVertex]+1){
                    dist[adjV]=dist[currentVertex]+1;
                    prev[adjV]= currentVertex;

                    switch (temp->type)
                    {
                    case 1:
                        updateKey(&list_type1, adjV, dist[adjV]);
                        break;
                    case 2:
                        updateKey(&list_type2, adjV, dist[adjV]);
                        break;
                    case 3:
                        updateKey(&list_type3, adjV, dist[adjV]);
                        break;
                    
                    default:
                        break;
                    }
                    
                }

            }
            temp = temp->next;
        }
        processed[currentVertex]=1;
    }

}



void CommercialLengths(struct net *net, int t) {


    int dist[MAX];
    int prev[MAX];
    dijkstra_lenght(net, t, dist, prev);  
    printf("Vertex   Distance from Source    Path\n");
    for (int i = 0; i < MAX; i++) {
        if(net->adj[i]!=NULL){
            if(dist[i]==INF){
                printf("%d \t\t Invalid \n", i);
            }else{
                printf("%d \t\t %d \t\t ", i, dist[i]);
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

    int dist[MAX];
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
                printf("%d \t\t %d \t\t ", s, dist[s]);
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
    int total_lengths[MAX]={0};
    int total_count=0;
    int dist[MAX];
    int prev[MAX];
    int max_length=0;
    for(int i=0;i<MAX;i++){
        if(net->adj[i]!=NULL){
            printf("%d\n",i);
            dijkstra_lenght(net, i, dist, prev);
            
            for (int j = 0; j < MAX; j++) {
                if (dist[j] != INF && dist[j] != 0) {  // Exclude unreachable nodes and the source itself
                    int length = dist[j];

                    total_lengths[length]++;
                    total_count++;
                    if(max_length<length){
                        max_length=length;
                    }
                }
            }
            
        } 
    }
    
    float ccdf;
    long total=total_count;
    for(int i=1;i<=max_length;i++){
        if(total_lengths[i]!=0){
            total=total-total_lengths[i];
            ccdf = (float)total / (float)total_count;
            printf("Length: %d, CCDF: %.6f, Amount: %d\n", i, ccdf, total_lengths[i]);
        }
        
    }
    

    
}

int removeHead(struct Node** head, struct Node** tail) {
    int data;
    if (*head == NULL) {
        // List is empty
        printf("List is empty, nothing to remove.\n");
        return -1;
    }

    // Store the current head and move the head pointer to the next node
    data=(*head)->data;
    struct Node* temp = *head;
    *head = (*head)->next;

    if (*head == NULL) {
        *tail = NULL;
    }
    // Free the old head
    free(temp);
    return data;
}


void appendNode_H_T(struct Node** head, struct Node** tail, int value) {
    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    // If the list is empty, the new node becomes both head and tail
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        // If the list is non-empty, append the new node at the tail
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void bfs_shortestAll(struct net *network, int node, int *dist, int *visited, int *total_lengths, int *total) {

    struct Node* head = NULL; 
    struct Node* tail = NULL;       
    insertAtBeginning(&head, node);

    for (int i = 0; i < MAX; i++) {
        if(network->adj[i]!=NULL){
            visited[i]=-1;
        }
    }

    tail=head;
    visited[node]=0;
    dist[node]=0;
    while (head != NULL) {
        int currentVertex = removeHead(&head, &tail);
        struct link* temp = network->adj[currentVertex];
        while (temp) {
            int adjV = temp->id;
            if(visited[adjV]==0){
                temp = temp->next;
                continue;
            } 
            dist[adjV] =dist[currentVertex]+1;
            total_lengths[dist[adjV]]++;
            (*total)++;
            visited[adjV] = 0;
            appendNode_H_T(&head, &tail, adjV);
            temp = temp->next;
        }
    }
}

void ShortestAll(struct net *net) {

    int dist[MAX];
    int visited[MAX];
    int total_lengths[MAX]={0};
    int total=0;

    for(int i=0; i<MAX;i++){
        if(net->adj[i]!=NULL){
            printf("%d\n",i);
            bfs_shortestAll(net, i, dist, visited,total_lengths,&total);
        }
    }

    double percentage;
    for(int i=0;i<MAX;i++){
        if(total_lengths[i]!=0){
            percentage = (double)total_lengths[i] / (double)total;
            printf("Length: %d, Percentage: %.6f, Amount: %d\n", i, percentage, total_lengths[i]);
        }
        
    }
    
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
