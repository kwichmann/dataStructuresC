# include <stdio.h>
# include "stack.h"

int main() {
    Stack stack = {0};

    push(&stack, 42);
    printf("Popped: %i\n", pop(&stack));

    return 0;
}
