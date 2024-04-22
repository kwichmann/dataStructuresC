#ifndef ARENAALLOCATOR_H
#define ARENAALLOCATOR_H

#include <stdlib.h>
#include <assert.h>

#define ALIGNMENT_SIZE 16

struct Arena {
    void* start;
    unsigned int size;
    unsigned int currentOffset;
};

typedef struct Arena Arena;

Arena makeArena(unsigned int size) {
    Arena arena;
    arena.start = malloc(size);
    arena.size = size;
    arena.currentOffset = 0;
    return(arena);
}

void* arenaAllocate(Arena *arena, unsigned int requestSize) {
    void* out = NULL;
    if (requestSize > 0) {
        requestSize = ((requestSize - 1) | (ALIGNMENT_SIZE - 1)) + 1;
        if (arena->currentOffset + requestSize <= arena->size) {
            out = arena->start + arena->currentOffset;
            arena->currentOffset += requestSize;
        }
    }
    return(out);
}

void arenaReset(Arena *arena) {
    arena->currentOffset = 0;
}

void freeArena(Arena *arena) {
    free(arena->start);
}

#endif
