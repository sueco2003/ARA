#include <stdio.h>
#include <stdlib.h>

#include "header.h"

//Creates a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

//Inserts a new node in the begining of a list
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    *head = newNode;
}

//removes the first node of the list
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

//Create and append a new node to the end of the list
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


/**
 * Using a BFS algorithm, it calculates the distance from a destination node to all nodes
 *
 * @param network A pointer to the network with loaded data.
 * @param node The AS that serves as destination for the algorithm execution
 * @param dist Vector with the distances of each node to the source node
 * @param visited Vector with the visited nodes
 * @param total_lengths Vector with the number of lengths in for each length
 * @param total The total amount of paths
 * @return void
 */
void bfs_shortestAll(struct net *network, int node, int *dist, int *visited, int *total_lengths, long *total) {

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


/**
 * Using a n*BFS algorithm, it calculates the lengths from all nodes to all nodes and prints the statistics
 *
 * @param network A pointer to the network with loaded data.
 * @return void
 */
void ShortestAll(struct net *net) {

    int dist[MAX];
    int visited[MAX];
    int total_lengths[MAX]={0};
    long total=0;

    int count = 0; 
    int progress = 10;

    for(int i=0; i<MAX;i++){
        if(net->adj[i]!=NULL){
            count++;
            if ((100 * count / net->V) >= progress) {
                printf("%d%% of vertices processed\n", progress);
                progress += 10; // Move to the next progress level (20%, 30%, etc.)
            }
            bfs_shortestAll(net, i, dist, visited,total_lengths,&total);
        }
    }

    //Statistics
    double percentage;
    long total_count=total;
    for(int i=0;i<MAX;i++){
        if(total_lengths[i]!=0){
            total=total-total_lengths[i];
            percentage = ((float)total / (float)total_count)*100;
            printf("Length: %d, CCDF: %.6f%%, Amount: %d\n", i, percentage, total_lengths[i]);
        }
        
    }
    
}