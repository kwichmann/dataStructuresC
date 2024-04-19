#include <assert.h>
#include "arenaAllocator.h"
#include "linkedList.h"

void test_empty() {
    printf("Testing empty list\n");
    List *list = NULL;
    assert(length(list) == 0);
    assert(peek(list, 0) == NULL);
}

void test_prepend(Arena *arena) {
    printf("Testing prepend\n");
    List *list = NULL;
    list = prepend(list, 60, arena);
    assert(length(list) == 1);
    assert(*peek(list, 0) == 60);
    list = prepend(list, 42, arena);
    assert(length(list) == 2);
    assert(*peek(list, 0) == 42);
    assert(*peek(list, 1) == 60);
}

void test_append(Arena *arena) {
    printf("Testing append\n");
    List *list = NULL;
    list = append(list, 60, arena);
    assert(length(list) == 1);
    assert(*peek(list, 0) == 60);
    list = append(list, 42, arena);
    assert(length(list) == 2);
    assert(*peek(list, 0) == 60);
    assert(*peek(list, 1) == 42);
}

void test_peek_poke(Arena *arena) {
    printf("Testing peek and poke\n");
    List *list = NULL;
    assert(peek(list, 0) == NULL);
    list = prepend(list, 60, arena);
    assert(*peek(list, 0) = 60);
    poke(list, 0, 42);
    assert(*peek(list, 0) = 42);
}

void test_insert(Arena *arena) {
    printf("Testing insert\n");
    List *list = NULL;
    list = prepend(list, 60, arena);
    list = append(list, 42, arena);
    assert(length(list) == 2);
    list = insert(list, 1, 123, arena);
    assert(length(list) == 3);
}

void all_tests(Arena *arena) {
    test_empty();
    test_prepend(arena);
    test_append(arena);
    test_peek_poke(arena);
    test_insert(arena);
}
