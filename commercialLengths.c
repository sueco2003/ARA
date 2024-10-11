#include <stdio.h>
#include <stdlib.h>

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

void dijkstra_lenght(struct net *graph, int src, long *dist, long *prev) {
        
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


    if(net->adj[t]==NULL){
        printf("There is no destination %d\n",t);
        return;
    }
    long dist[MAX];
    long prev[MAX];
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

    if(net->adj[t]==NULL){
        printf("There is no destination %d\n",t);
        return;
    }
    long dist[MAX];
    long prev[MAX];
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
            if(net->adj[s]==NULL){
                printf("%d is not a source\n",s);
                continue;
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
    long total_lengths[MAX]={0};
    long total_count=0;
    long dist[MAX];
    long prev[MAX];
    long max_length=0;
    int count = 0; 
    int progress = 10;
    for(int i=0;i<MAX;i++){
        if(net->adj[i]!=NULL){
            dijkstra_lenght(net, i, dist, prev);
            count++;
            if ((100 * count / net->V) >= progress) {
                printf("%d%% of vertices processed\n", progress);
                progress += 10; // Move to the next progress level (20%, 30%, etc.)
            }
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
    
    double ccdf;
    long total=total_count;
    for(int i=1;i<=max_length;i++){
        if(total_lengths[i]!=0){
            total=total-total_lengths[i];
            ccdf = ((float)total / (float)total_count)*100;
            printf("Length: %d, CCDF: %.6f%%, Amount: %ld\n", i, ccdf, total_lengths[i]);
        }
        
    }
    

    
}