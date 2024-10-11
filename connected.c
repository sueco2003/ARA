#include <stddef.h>
#include <stdio.h>

#include "header.h"

bool isStronglyConnected;

/**
 * It looks for tier-1 AS and checks if them can connect to each other.
 *
 * @param net A pointer to the network with loaded data.

 * @return void
 */

void connectAnalysis(const struct net *net) {
    int tier1Count = 0, tier1[MAX] = {0}, i;

    for (i = 0; i < MAX; i++) {
        if (net->adj[i] != NULL) {
            int valid = 1;
            const struct link *temp = net->adj[i];
            while (temp != NULL) {
                if (temp->type == 3) {
                    valid = 0;
                    break;
                }
                temp = temp->next;
            }
            if (valid) {
                tier1Count++;
                tier1[i] = 1;
            }
        }
    }
    for (i = 0; i < MAX; i++) {
        if (tier1[i]) {
            int tier1Peers = 0;
            const struct link *temp = net->adj[i];
            while (temp != NULL) {
                if (temp->type != 2 || !tier1[temp->id]) {
                    temp = temp->next;
                    continue;
                }
                tier1Peers++;
                temp = temp->next;
            }
            if (tier1Peers != tier1Count - 1) {
                isStronglyConnected = 0;
                return;
            }
        }
    }
    isStronglyConnected = 1;
}

/**
 * Tells the user if the input network is commercially connected or not.
 *
 * @return void
 */

void CommercialConnected() {
    if (!isStronglyConnected) {
        printf("The network is not strongly connected!\n");
    }
    else {
        printf("The network is strongly connected!\n");
    }
}