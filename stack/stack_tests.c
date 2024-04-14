#include <assert.h>
#include "stack.h"

void test_empty_full() {
    printf("Testing empty/full chekcs\n");
    Stack stack = {0};
    assert(isEmpty(&stack));
    for (int i; i < STACK_SIZE; i++) {
        push(&stack, 42);
    }
    assert(isFull(&stack));
}

void test_push_peek_pop() {
    printf("Testing push/peek/pop\n");
    Stack stack = {0};
    for (int i = 0; i < 10; i++) {
        assert(stack.top == i);
        push(&stack, i);
        assert(peek(&stack) == i);
        assert(stack.top == i + 1);
        assert(pop(&stack) == i);
        assert(stack.top == i);
        push(&stack, 42);
    }
}

void all_tests() {
    test_empty_full();
    test_push_peek_pop();
}
