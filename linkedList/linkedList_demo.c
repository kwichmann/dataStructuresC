#include <stdio.h>
#include "arenaAllocator.h"
#include "linkedList.h"
#include "linkedList_tests.c"

int main() {
    Arena arena = makeArena(2048);
    all_tests(&arena);

    return 0;
}
