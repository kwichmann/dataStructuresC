#include <assert.h>

void test_initialization() {
    printf("Testing initialization\n");
    DynamicArray dyn = initialize();
    assert(dyn.size == 0);
    assert(dyn.capacity == START_SIZE);
}

void test_copy() {
    printf("Testing copy\n");
    DynamicArray dyn = initialize();
    DynamicArray dyn_copy = copy(&dyn);
    assert(dyn.size == dyn_copy.size);
    assert(dyn.capacity == dyn_copy.capacity);
    assert(&dyn != &dyn_copy);
}

void test_upsize_downsize() {
    printf("Testing upsizing and downsizing\n");
    DynamicArray dyn = initialize();
    assert(dyn.capacity == START_SIZE);
    upSize(&dyn);
    assert(dyn.capacity == 2 * START_SIZE);
    upSize(&dyn);
    assert(dyn.capacity == 4 * START_SIZE);
    downSize(&dyn);
    assert(dyn.capacity == 2 * START_SIZE);
    downSize(&dyn);
    assert(dyn.capacity == START_SIZE);
    downSize(&dyn);
    assert(dyn.capacity == START_SIZE / 2);
}

void test_append() {
    printf("Testing append\n");
    DynamicArray dyn = initialize();
    for (int i = 0; i < 10; i++) {
        append(&dyn, i);
        assert(dyn.size == i + 1);
        assert(peek(&dyn, i) == i);
    }
}

void test_prepend() {
    printf("Testing prepend\n");
    DynamicArray dyn = initialize();
    for (int i = 0; i < 10; i++) {
        prepend(&dyn, i);
        assert(dyn.size == i + 1);
    }
}

void test_detach() {
    printf("Testing detach\n");
    DynamicArray dyn = initialize();
    for (int i = 0; i < 10; i++) {
        append(&dyn, i);
    }
    for (int i = 0; i < 10; i++) {
        assert(detach(&dyn) == 9 - i);
        assert(dyn.size == 9 - i);
    }
}

void test_pretach() {
    printf("Testing pretach\n");
    DynamicArray dyn = initialize();
    for (int i = 0; i < 10; i++) {
        append(&dyn, i);
    }
    for (int i = 0; i < 10; i++) {
        assert(pretach(&dyn) == i);
        assert(dyn.size == 9 - i);
    }
}

void test_insert() {
    printf("Testing insert\n");
    DynamicArray dyn = initialize();
    for (int i = 0; i < 10; i++) {
        append(&dyn, i);
    }
    for (int i = 0; i < 10; i++) {
        insert(&dyn, 2 * i, 42);
        assert(dyn.size == 11 + i);
        assert(peek(&dyn, 2 * i) == 42);
        assert(peek(&dyn, 2 * i + 1) == i);
    }
}

void test_delete() {
    printf("Testing delete\n");
    DynamicArray dyn = initialize();
    for (int i = 0; i < 10; i++) {
        append(&dyn, i);
    }
    for (int i = 0; i < 5; i++) {
        delete(&dyn, i);
        assert(dyn.size == 9 - i);
        assert(peek(&dyn, i) == 2 * i + 1);
    }
}

void test_peek_poke() {
    printf("Testing peek and poke\n");
    DynamicArray dyn = initialize();
    for (int i = 0; i < 10; i++) {
        append(&dyn, i);
    }
    for (int i = 0; i < 10; i++) {
        assert(peek(&dyn, i) == i);
        poke(&dyn, i, 2 * i);
        assert(peek(&dyn, i) == 2 * i);
    }
}

void all_tests() {
    test_initialization();
    test_copy();
    test_upsize_downsize();
    test_append();
    test_prepend();
    test_detach();
    test_pretach();
    test_insert();
    test_delete();
    test_peek_poke();
}