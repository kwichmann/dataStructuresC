#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
    fnv1a hashing function as described here:
    https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
*/

#define FNV_offset_basis 0xcbf29ce484222325
#define FNV_prime 0x100000001b3

unsigned long long int fnv1a(char *data) {
    unsigned long long int hash = FNV_offset_basis;
    int index = 0;
    while (data[index] != 0) {
        hash = hash ^ data[index];
        hash *= FNV_prime;
        index++;
    }
    return(hash);
}

#define LOG2NUMBER_OF_BUCKETS 4
#define NUMBER_OF_BUCKETS (1 << LOG2NUMBER_OF_BUCKETS)
#define HASH_MASK (NUMBER_OF_BUCKETS - 1)

struct BucketItem {
    unsigned long long int hash;
    int value;
};

typedef struct BucketItem BucketItem;

// Buckets are dynamic arrays
#define BUCKET_START_CAPACITY 4

struct Bucket {
    int capacity;
    int size;
    BucketItem *array;
};

typedef struct Bucket Bucket;

Bucket init_bucket() {
    Bucket bucket;
    bucket.capacity = BUCKET_START_CAPACITY;
    bucket.size = 0;
    bucket.array = malloc(BUCKET_START_CAPACITY * sizeof(BucketItem));
    return(bucket);
}

void show_bucket(Bucket *bucket) {
    for (int i = 0; i < bucket->size; i++) {
        printf("\tHash: %llx, Value: %i\n", bucket->array[i].hash, bucket->array[i].value);
    }
}

void upsize_bucket(Bucket *bucket) {
    bucket->capacity *= 2;
    bucket->array = realloc(bucket->array, bucket->capacity * sizeof(BucketItem));
}

void downsize_bucket(Bucket *bucket) {
    bucket->capacity /= 2;
    bucket->array = realloc(bucket->array, bucket->capacity * sizeof(BucketItem));
}

void add_to_bucket(Bucket *bucket, unsigned long long int hash, int value) {
    for (int i = 0; i < bucket->size; i++) {
        if (bucket->array[i].hash == hash) {
            bucket->array[i].value = value;
            return;
        }
    }
    if (bucket->size == bucket->capacity) {
        upsize_bucket(bucket);
    }
    bucket->array[bucket->size].hash = hash;
    bucket->array[bucket->size++].value = value;
}

int* lookup_in_bucket(Bucket *bucket, unsigned long long int hash) {
    static int out; // Will this cause memory leak?
    for (int i = 0; i < bucket->size; i++) {
        if (bucket->array[i].hash == hash) {
            out = bucket->array[i].value;
            return(&out);
        }
    }
    return(NULL);
}

int* delete_from_bucket(Bucket *bucket, unsigned long long int hash) {
    static int out; // Will this cause memory leak?
    for (int i = 0; i < bucket->size; i++) {
        if (bucket->array[i].hash == hash) {
            out = bucket->array[i].value;
            if (bucket->size < bucket->capacity / 4) {
                downsize_bucket(bucket);
            }
            memmove(&bucket->array[i], &bucket->array[i + 1], (bucket->size - i - 1) * sizeof(BucketItem));
            bucket->size--;
            return(&out);
        }
    }
    return(NULL);
}

struct HashMap {
    Bucket buckets[NUMBER_OF_BUCKETS];
};

typedef struct HashMap HashMap;

void init_hashMap(HashMap *hashMap) {
    for (int i = 0; i < NUMBER_OF_BUCKETS; i++) {
        hashMap->buckets[i] = init_bucket();
    }
}

void show_hashMap(HashMap *hashMap) {
    for (int i = 0; i < NUMBER_OF_BUCKETS; i++) {
        printf("Bucket %i:\n", i);
        show_bucket(&hashMap->buckets[i]);
    }
}

void add_item(HashMap *hashMap, char *key, int value) {
    unsigned long long int hash = fnv1a(key);
    int bucketNumber = (int) hash & HASH_MASK;
    add_to_bucket(&(hashMap->buckets[bucketNumber]), hash, value);
}

int lookup_item(HashMap *hashMap, char *key) {
    unsigned long long int hash = fnv1a(key);
    int bucketNumber = (int) hash & HASH_MASK;
    int* lookup = lookup_in_bucket(&(hashMap->buckets[bucketNumber]), hash);
    assert(lookup != NULL);
    return(*lookup);
}

int delete_item(HashMap *hashMap, char *key) {
    unsigned long long int hash = fnv1a(key);
    int bucketNumber = (int) hash & HASH_MASK;
    int* lookup = delete_from_bucket(&(hashMap->buckets[bucketNumber]), hash);
    assert(lookup != NULL);
    return(*lookup);
}

#endif