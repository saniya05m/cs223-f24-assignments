/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva
 * Date: 12/06/2024
 * Description: Program that outputs benchmark statistics about malloc
 ---------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "rand.h"

#define ROUNDS 3
#define BUFFER 5
#define LOOP 10

struct chunk {
    int size;
    int used;
    struct chunk *next;
};

void memstats(struct chunk *freelist, void *buffer[], int len) {
    int totalBlocks = 0, usedBlocks = 0, freedBlocks = 0;
    int totalMem = 0, usedMem = 0, freeMem = 0, unusedMem = 0;

    for (int i = 0; i < len; ++i) {
        if (buffer[i] != NULL) {
            struct chunk *currentChunk = (struct chunk *)((struct chunk *)buffer[i] - 1);
            totalMem += currentChunk->size;
            unusedMem += currentChunk->size - currentChunk->used;
            usedMem += currentChunk->size;
            ++totalBlocks;
        }
    }

    while (freelist != NULL) {
        ++freedBlocks;
        ++totalBlocks;
        freeMem += freelist->size;
        freelist = freelist->next;
    }

    usedBlocks = totalBlocks - freedBlocks;

    printf("Total blocks: %d Free blocks: %d Used blocks: %d\n", totalBlocks, freedBlocks, usedBlocks);
    printf("Total memory allocated: %d Free memory: %d Used memory: %d\n", totalMem + freeMem, freeMem, usedMem);
    printf("Underutilized memory: %0.2f\n", (float)unusedMem / totalMem);
}

int main(int argc, char *argv[]) {
    printf("Starting test..\n");

    srand(100);

    struct timeval tstart, tend;
    double timer;

    gettimeofday(&tstart, NULL);

    void *buffer[BUFFER] = {NULL};

    void *initialHeapTop = sbrk(0);
    void *currentHeapTop;

    printf("The initial top of the heap is %p.\n", initialHeapTop);

    for (int round = 0; round < ROUNDS; ++round) {
        printf("---------------\n%d\n", round);

        for (int iteration = 0; iteration < LOOP; ++iteration) {
            int bufferIndex = rand() % BUFFER;

            if (buffer[bufferIndex] != NULL) {
                free(buffer[bufferIndex]);
                buffer[bufferIndex] = NULL;
                printf("Freeing index %d\n", bufferIndex);
            } else {
                size_t allocationSize = (size_t)randExp(8, 4000);
                int *allocatedMemory = malloc(allocationSize);

                if (allocatedMemory == NULL) {
                    fprintf(stderr, "malloc failed\n");
                    return 1;
                }

                *allocatedMemory = 123;
                buffer[bufferIndex] = allocatedMemory;
                printf("Allocating %d bytes at index %d\n", (int)allocationSize, bufferIndex);
            }
        }

        extern struct chunk *flist;
        currentHeapTop = sbrk(0);
        int heapGrowth = (int)(currentHeapTop - initialHeapTop);
        initialHeapTop = currentHeapTop;

        printf("The new top of the heap is %p.\n", currentHeapTop);
        printf("Increased by %d (0x%x) bytes\n", heapGrowth, heapGrowth);
        memstats(flist, buffer, BUFFER);
    }

    for (int i = 0; i < BUFFER; ++i) {
        free(buffer[i]);
    }

    gettimeofday(&tend, NULL);
    timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec) / 1.e6;
    printf("Time is %g\n", timer);

    return 0;
}

