#include <assert.h>
#include "../arenaAllocator/arenaAllocator.h"
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

void test_tails(Arena *arena) {
    printf("Testing tail and second-to-last\n");
    List *list = NULL;
    assert(tail(list) == NULL);
    assert(second_to_last(list) == NULL);
    list = prepend(list, 42, arena);
    assert(tail(list)->value == 42);
    assert(second_to_last(list) == NULL);
    list = append(list, 60, arena);
    assert(tail(list)->value == 60);
    assert(second_to_last(list)->value == 42);
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

void test_pretach(Arena *arena) {
    printf("Testing pretach\n");
    List *list = NULL;
    list = append(list, 1, arena);
    list = append(list, 2, arena);
    list = pretach(list);
    assert(length(list) == 1);
    assert(list->value == 2);
}

void test_detach(Arena *arena) {
    printf("Testing detach\n");
    List *list = NULL;
    list = append(list, 1, arena);
    list = append(list, 2, arena);
    list = detach(list);
    assert(length(list) == 1);
    assert(list->value == 1);
}

void test_delete(Arena *arena) {
    printf("Testing delete\n");
    List *list = NULL;
    list = append(list, 1, arena);
    list = delete(list, 0);
    assert(length(list) == 0);
    list = append(list, 1, arena);
    list = append(list, 2, arena);
    list = append(list, 3, arena);
    assert(length(list) == 3);
    delete(list, 1);
    assert(length(list) == 2);
    assert(*peek(list, 0) == 1);
    assert(*peek(list, 1) == 3);
    delete(list, 1);
    assert(length(list) == 1);
    assert(*peek(list, 0) == 1);
}

void all_tests(Arena *arena) {
    test_empty();
    test_prepend(arena);
    test_append(arena);
    test_tails(arena);
    test_peek_poke(arena);
    test_insert(arena);
    test_pretach(arena);
    test_detach(arena);
    test_delete(arena);
}
