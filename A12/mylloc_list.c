/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva
 * Date: 12/06/2024
 * Description: Program that implements malloc and free 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
    int size;
    int used;
    struct chunk *next;
};

struct chunk *flist = NULL;

void *malloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    struct chunk *current = flist;
    struct chunk *previous = NULL;

    while (current != NULL) {
        if (current->size >= size) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                flist = current->next;
            }
            current->used = size;
            return (void *)(current + 1);
        }
        previous = current;
        current = current->next;
    }

    void *new_memory = sbrk(size + sizeof(struct chunk));
    if (new_memory == (void *)-1) {
        return NULL;
    }

    struct chunk *new_chunk = (struct chunk *)new_memory;
    new_chunk->size = (int)size;
    new_chunk->used = size;
    return (void *)(new_chunk + 1);
}

void free(void *memory) {
    if (memory == NULL) {
        return;
    }

    struct chunk *chunk_to_free = (struct chunk *)memory - 1;
    chunk_to_free->next = flist;
    flist = chunk_to_free;
}

