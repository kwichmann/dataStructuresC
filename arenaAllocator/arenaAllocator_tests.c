#include <assert.h>
#include "arenaAllocator.h"

void test_allocation() {
    printf("Testing arena allocation\n");
    Arena arena = makeArena(1024);
    assert(arena.size == 1024);
    assert(arena.currentOffset == 0);
    void* myAllocation = arenaAllocate(&arena, 512);
    assert(arena.currentOffset == 512);
    void* myAllocation2 = arenaAllocate(&arena, 256);
    assert(arena.currentOffset == 768);
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
    unsigned int abc_size = sizeof(Abc);
    Arena arena = makeArena(4 * abc_size);
    Abc* abc1 = (Abc*) arenaAllocate(&arena, abc_size);
    abc1->a = 1;
    abc1->b = 11;
    abc1->c = 111;
    Abc* abc2 = (Abc*) arenaAllocate(&arena, abc_size);
    abc2->a = 2;
    abc2->b = 22;
    abc2->c = 222;
}

void all_tests() {
    test_allocation();
    test_struct_casting();
}
