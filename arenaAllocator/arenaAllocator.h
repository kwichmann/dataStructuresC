#ifndef ARENAALLOCATOR_H
#define ARENAALLOCATOR_H

#include <stdlib.h>
#include <assert.h>

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
    assert(arena->currentOffset + requestSize < arena->size);
    void* out = arena->start + arena->currentOffset;
    arena->currentOffset += requestSize;
    return(out);
}

void freeArena(Arena *arena) {
    free(arena->start);
}

#endif
