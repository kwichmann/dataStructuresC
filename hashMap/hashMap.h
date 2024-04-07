#ifndef HASHMAP_H
#define HASHMAP_H

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

#endif