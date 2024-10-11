//
// Created by guilh on 10/09/2024.
//
#pragma once

#define HEADER_H
#include <stdbool.h>

#define MAX 65636 // In case there are 100 cycles MAX
#define INF 4294836225L

struct link {
    int id;
    int type;
    struct link *next;
};


struct net {
    int E;
    long long V;
    struct link *adj[MAX];
};

struct Node {
    int data;
    struct Node* next;
};

extern bool isCyclic, isStronglyConnected;

int interface();



// Network related methods
struct net *createNet();
void createEdge(struct net *net, int source, int destination, int type);
void removeEdge(struct net *network, int source, int destination);
void freeNet(struct net *net);

// Utility methods
struct net *OpenFile(const char *filename, struct net *net);
int isValidRoute(int prevType, int currentType);

// Commercial related methods
int *Commercial(const struct net *network, int t, int option);
void appendNode(struct Node **head, int vertex, const int *visitedLinkType);
int removeNode(struct Node **head);
void printPath(int node, const int *parent);
void CommercialAll(const struct net *network);

// CommercialCycle related methods
void findStronglyConnectedComponentsUtil(struct net *network, int v);
void findStronglyConnectedComponents(struct net *network);
void cycleRefactor(struct net *network);
void printPath(int node, const int *parent);
void CommercialCycle();

// CommercialConnected related methods
void connectAnalysis(const struct net *net);
void CommercialConnected();


