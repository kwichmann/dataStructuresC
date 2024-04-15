#include <assert.h>
#include "arenaAllocator.h"

void test_allocation() {
    printf("Testing arena allocation\n");
    Arena arena = makeArena(1024);
    assert(arena.size == 1024);
    assert(arena.currentOffset == 0);
    // 0 byte allocation not allowed
    assert(arenaAllocate(&arena, 0) == NULL);
    assert(arena.currentOffset == 0);
    // Allocations make offset grow
    void* myAllocation = arenaAllocate(&arena, 512);
    assert(arena.currentOffset == 512);
    void* myAllocation2 = arenaAllocate(&arena, 256);
    assert(arena.currentOffset == 768);
    // Too large allocation
    assert(arenaAllocate(&arena, 2048) == NULL);
    assert(arena.currentOffset == 768);
    // Alignment
    void* myAllocation3 = arenaAllocate(&arena, 12);
    assert(arena.currentOffset == 768 + ALIGNMENT_SIZE);
    // Reset
    arenaReset(&arena);
    assert(arena.currentOffset == 0);
    freeArena(&arena);
}

struct Abc {
    int a;
    int b;
    int c;
};

typedef struct Abc Abc;

void test_struct_casting() {
    printf("Testing arena allocation of simple struct\n");
    // Round up size of struct to account for alignment
    unsigned int abc_size = sizeof(Abc);
    abc_size = ((abc_size - 1) | (ALIGNMENT_SIZE - 1)) + 1;
    // Make room for two structs
    Arena arena = makeArena(2 * abc_size);
    // Cast arena allocations to struct
    Abc* abc1 = (Abc*) arenaAllocate(&arena, abc_size);
    abc1->a = 1;
    abc1->b = 11;
    abc1->c = 111;
    Abc* abc2 = (Abc*) arenaAllocate(&arena, abc_size);
    abc2->a = 2;
    abc2->b = 22;
    abc2->c = 222;
    // No room for a third struck in arena
    assert(arenaAllocate(&arena, abc_size) == NULL);
    freeArena(&arena);
}

void all_tests() {
    test_allocation();
    test_struct_casting();
}
