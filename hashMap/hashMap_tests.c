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

void test_bucket_upsize_downsize() {
    printf("Testing bucket upsizing and downsizing\n");
    Bucket bucket = init_bucket();
    assert(bucket.capacity == BUCKET_START_CAPACITY);
    upsize_bucket(&bucket);
    assert(bucket.capacity == 2 * BUCKET_START_CAPACITY);
    upsize_bucket(&bucket);
    assert(bucket.capacity == 4 * BUCKET_START_CAPACITY);
    downsize_bucket(&bucket);
    assert(bucket.capacity == 2 * BUCKET_START_CAPACITY);
    downsize_bucket(&bucket);
    assert(bucket.capacity == BUCKET_START_CAPACITY);
    downsize_bucket(&bucket);
    assert(bucket.capacity == BUCKET_START_CAPACITY / 2);
}

void test_bucket_add_lookup_delete() {
    printf("Testing bucket element addition, lookup, and deletion\n");
    Bucket bucket = init_bucket();
    // Empty bucket
    assert(bucket.size == 0);
    assert(lookup_in_bucket(&bucket, 0) == NULL);
    // Add one element 
    add_to_bucket(&bucket, 0, 42);
    assert(bucket.size == 1);
    assert(*lookup_in_bucket(&bucket, 0) == 42);
    // Overwrite element
    add_to_bucket(&bucket, 0, 60);
    assert(bucket.size == 1);
    assert(*lookup_in_bucket(&bucket, 0) == 60);
    // Many elements
    for (int i = 0; i < 10; i++) {
        add_to_bucket(&bucket, i, i);
        assert(bucket.size == i + 1);
    }
    // Delete element
    assert(*lookup_in_bucket(&bucket, 5) == 5);
    delete_from_bucket(&bucket, 5);
    assert(bucket.size == 9);
    assert(lookup_in_bucket(&bucket, 5) == NULL);
}

void test_hashMap() {
    HashMap hashMap;
    // Empty hash map
    init_hashMap(&hashMap);
    assert(length_hashMap(&hashMap) == 0);
    // Single element
    add_item(&hashMap, "key", 777);
    assert(length_hashMap(&hashMap) == 1);
    assert(lookup_item(&hashMap, "key") == 777);
    // Overwrite element
    add_item(&hashMap, "key", 1234);
    assert(length_hashMap(&hashMap) == 1);
    assert(lookup_item(&hashMap, "key") == 1234);
    // Remove element
    delete_item(&hashMap, "key");
    assert(length_hashMap(&hashMap) == 0);
    // Many elements - one for each letter in the alphabet
    for (int ch = 0x41; ch <= 0x5a; ch++) {
        char str[2];
        str[0] = ch;
        str[1] = 0;
        add_item(&hashMap, str, ch);
    }
    // show_hashMap(&hashMap);
    assert(length_hashMap(&hashMap) == 26);
    assert(lookup_item(&hashMap, "A") == 65);
    assert(lookup_item(&hashMap, "Z") == 90);
}

void test_all() {
    test_hashFunction();
    test_bucket_upsize_downsize();
    test_bucket_add_lookup_delete();
    test_hashMap();
}
