#ifndef LOBSTERS_H
#define LOBSTERS_H

typedef struct {
    float size;
    float value;
} Lobster;

Lobster* allocateLobsters(int number);
void freeLobsters(Lobster *lobsters);
float calculateTotalValue(Lobster *lobsters, int number, float capacity);

#endif // LOBSTERS_H
