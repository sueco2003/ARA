//
// Created by guilh on 10/09/2024.
//
#ifndef HEADER_H
#define HEADER_H
#include <stdbool.h>

#define MAX 65535
#define INF 65536

struct link {
    int id;
    int type;
    struct link *next;
};


struct net {
    int E;
    int V;
    struct link *adj[MAX];
};

struct Node {
    int data;
    struct Node* next;
};

int interface();
void Commercial(struct net *net, int t);
void CommercialTest(struct net *net, int s, int t);
void CommercialCycle(struct net *net);
void CommercialConnected(struct net *net);
void CommercialLengths(struct net *net, int t);
void CommercialLengthsAll(struct net *net);
void ShortestAll(struct net *net);
struct net *OpenFile(const char *filename, struct net *net);
bool createEdge(struct net *net, int source, int destination, int type);
struct link *createAdjacency(int destination, int type);

struct net *createNet();
void dfs(struct net* network, int node, int prevType, int *visitedLinkType);
void clearInputBuffer();
struct net* reverseNet(struct net* network);
int canAllReachTarget(struct net* network, int targetNode);
int isInvalidRoute(int prevType, int currentType);
int dfs_cycle(struct net *network, int node, int prevType, int *visitedLinkType);
int isCyclicUtil(struct net *network, int node, int *visited, int *recStack);
int isCyclic(struct net *net);
void kosaraju(struct net *graph);
void dfsTransposed(struct net *graph, int v, bool visited[], int prevType);
void transposeGraph(struct net *graph, struct net *transposed);
void dfsOriginal(struct net *graph, int v, bool visited[], int *stack, int *stackIndex, int prevType);
void CommercialLengthsTest(struct net *net, int t);



#endif HEADER_H