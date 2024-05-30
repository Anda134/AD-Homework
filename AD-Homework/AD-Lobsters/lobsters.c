#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lobsters.h"

Lobster* allocateLobsters(int number) {
    Lobster* lobsters = (Lobster*)malloc(number * sizeof(Lobster));
    return lobsters;
}

void freeLobsters(Lobster *lobsters) {
    free(lobsters);
}

float calculateTotalValue(Lobster *lobsters, int number, float capacity) {
    float *K = (float *)malloc((int)(capacity + 1) * sizeof(float));
    for(int i = 0; i <= (int)capacity; i++) K[i] = 0;

    for(int i = 0; i < number; i++) {
        for(int w = (int)capacity; w >= (int)lobsters[i].size; w--) {
            if(lobsters[i].value + K[w - (int)lobsters[i].size] > K[w])
                K[w] = lobsters[i].value + K[w - (int)lobsters[i].size];
        }
    }

    float totalValue = K[(int)capacity];
    free(K);
    return totalValue;
}
