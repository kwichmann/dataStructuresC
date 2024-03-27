# include <stdlib.h>
# include <stdbool.h>
const int STACK_SIZE = 16;

struct Stack {
    int items[STACK_SIZE];
    int top;
};

typedef struct Stack Stack;

Stack* newStack() {
    Stack* stack = malloc(sizeof(Stack));
    stack->top = -1;
    return(stack);
}

void emptyStack(Stack* stack) {
    stack->top = -1;
}

bool isEmpty(Stack* stack) {
    return(stack->top == -1);
}

bool isFull(Stack* stack) {
    return(stack->top == STACK_SIZE - 1);
}

void push(Stack* stack, int item) {
    stack->top++;
    stack->items[stack->top] = item;
}

int pop(Stack* stack) {
    int out = stack->items[stack->top];
    stack->top--;
    return(out);
}
