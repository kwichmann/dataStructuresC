#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define STACK_SIZE 16

struct Stack {
    int items[STACK_SIZE];
    int top;
};

typedef struct Stack Stack;

bool isEmpty(Stack* stack) {
    return(stack->top == 0);
}

bool isFull(Stack* stack) {
    return(stack->top == STACK_SIZE);
}

void push(Stack* stack, int item) {
    assert(!isFull(stack));
    stack->items[stack->top++] = item;
}

int peek(Stack* stack) {
    assert(!isEmpty(stack));
    return(stack->items[stack->top - 1]);
}

int pop(Stack* stack) {
    assert(!isEmpty(stack));
    return(stack->items[--stack->top]);
}

