#include <stdio.h>
#include "dynamicArray.h"
#include "dynamicArray_tests.c"

int main() {
DynamicArray dyn = initialize();
    all_tests();
    return 0;
}