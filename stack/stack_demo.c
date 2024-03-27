# include <stdio.h>
# include "stack.h"

int main() {
    Stack* pStack = newStack();
    push(pStack, 42);
    printf("Popped: %i\n", pop(pStack));

    free(pStack);
    return 0;
}
