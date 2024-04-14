#include <stdio.h>
#include "hashMap.h"
#include "hashMap_tests.c"

int main() {
    test_all();

    HashMap hashMap;
    init_hashMap(&hashMap);
    add_item(&hashMap, "yolo", 42);
    add_item(&hashMap, "b", 69);
    add_item(&hashMap, "bb", 333);
    add_item(&hashMap, "bbb", 444);
    add_item(&hashMap, "bbbb", 555);
    add_item(&hashMap, "bbbb", 666);
    printf("%i\n", lookup_item(&hashMap, "bbbb"));
    delete_item(&hashMap, "bbbb");
    show_hashMap(&hashMap);

    return(0);
}