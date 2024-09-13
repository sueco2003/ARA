//
// Created by guilh on 10/09/2024.
//
#ifndef HEADER_H
#define HEADER_H
#include <stdbool.h>

#define MAX 65535

struct link {
    int id;
    int type;
    struct link *next;
};


struct net {
    int E;
    struct link *adj[MAX];
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
int isValidRoute(int prevType, int currentType);

#endif HEADER_H