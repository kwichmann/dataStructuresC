# include <stdlib.h>
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
};

void push(Stack* stack, int item) {
    stack->top++;
    stack->items[stack->top] = item;
};

int pop(Stack* stack) {
    int out = stack->items[stack->top];
    stack->top--;
    return(out);
};
