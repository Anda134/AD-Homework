#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lobsters.h"

int main() {
    FILE *inputFile = fopen("data.in", "r");
    FILE *outputFile = fopen("data.out", "w");
    if (inputFile == NULL || outputFile == NULL) {
        perror("Failed to open input/output file");
        return 1;
    }


    int numTestCases;
    if (fscanf(inputFile, "%d", &numTestCases) != 1 || numTestCases <= 0) {
        fprintf(outputFile, "Invalid number of test cases.\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }
    fprintf(outputFile, "Number of test cases: %d\n", numTestCases);

    struct timespec start, end;
    double cpu_time_used;

    for (int t = 0; t < numTestCases; ++t) {
        int number;
        float capacity;
        if (fscanf(inputFile, "%d", &number) != 1 || number <= 0) {
            fprintf(outputFile, "Invalid input for test case %d. Please enter a positive integer.\n", t + 1);
            continue; // Move to the next test case
        }
        fprintf(outputFile, "Number of lobsters in test case %d: %d\n", t + 1, number);

        // Allocate memory for lobsters
        Lobster *lobsters = allocateLobsters(number);
        if (lobsters == NULL) {
            fprintf(outputFile, "Memory allocation failed for test case %d.\n", t + 1);
            continue; // Move to the next test case
        }

        // Input lobster details
        for (int i = 0; i < number; ++i) {
            if (fscanf(inputFile, "%f %f", &lobsters[i].size, &lobsters[i].value) != 2) {
                fprintf(outputFile, "Invalid input for lobster %d in test case %d.\n", i + 1, t + 1);
                freeLobsters(lobsters);
                continue; // Move to the next test case
            }
        }

        if (fscanf(inputFile, "%f", &capacity) != 1 || capacity <= 0) {
            fprintf(outputFile, "Invalid input for capacity in test case %d. Please enter a positive float.\n", t + 1);
            freeLobsters(lobsters);
            continue; // Move to the next test case
        }
        fprintf(outputFile, "Capacity for test case %d: %f\n", t + 1, capacity);

        // Start timing
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Calculate total value
        float totalValue = calculateTotalValue(lobsters, number, capacity);
        fprintf(outputFile, "Test case %d: The total value of gold coins is: %f\n", t + 1, totalValue);

        // Stop timing
        clock_gettime(CLOCK_MONOTONIC, &end);

        // Calculate CPU time used
        cpu_time_used = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        fprintf(outputFile, "Test case %d: CPU time used: %f seconds\n", t + 1, cpu_time_used);

        // Free allocated memory
        freeLobsters(lobsters);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
