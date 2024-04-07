#include <assert.h>
#include "hashMap.h"

void test_hashFunction() {
    printf("Testing hash function fnv1a\n");
    /*
        Reference hash values calculated at:
        https://md5calc.com/hash/fnv1a64
    */
    assert(fnv1a("Hello") == 0x63f0bfacf2c00f6b);
    assert(fnv1a("My hovercraft is full of eels") == 0x0c82f7ec920ebe58);
}

void test_all() {
    test_hashFunction();
}
