#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define START_SIZE 4

struct DynamicArray {
    int capacity;
    int size;
    int *array;
};

typedef struct DynamicArray DynamicArray;

DynamicArray initialize() {
    DynamicArray dynArray;
    dynArray.capacity = START_SIZE;
    dynArray.size = 0;
    dynArray.array = malloc(START_SIZE * sizeof(int));
    return(dynArray);
}

void show(DynamicArray *dArray) {
    for (int i = 0; i < dArray->size; i++) {
        printf("Entry %i: %i\n", i, dArray->array[i]);
    }
}

DynamicArray copy(DynamicArray *dArray) {
    DynamicArray arrayCopy;
    arrayCopy.capacity = dArray->capacity;
    arrayCopy.size = dArray->size;
    arrayCopy.array = malloc(dArray->capacity * sizeof(int));
    for (int i = 0; i < dArray->size; i++) {
        arrayCopy.array[i] = dArray->array[i];
    }
    return(arrayCopy);
}

void upSize(DynamicArray *dArray) {
    dArray->capacity *= 2;
    dArray->array = realloc(dArray->array, dArray->capacity * sizeof(int));
}

void downSize(DynamicArray *dArray) {
    assert(dArray->capacity >= 2);
    dArray->capacity /= 2;
    assert(dArray->size <= dArray->capacity);
    dArray->array = realloc(dArray->array, dArray->capacity * sizeof(int));
}

void append(DynamicArray *dArray, int item) {
    if (dArray->size == dArray->capacity) {
        upSize(dArray);
    }
    dArray->array[dArray->size++] = item;
}

void prepend(DynamicArray *dArray, int item) {
    if (dArray->size == dArray->capacity) {
        upSize(dArray);
    }
    for (int i = dArray->size; i > 0; i--) {
        dArray->array[i] = dArray->array[i - 1];
    }
    dArray->array[0] = item;
    dArray->size++;
}

int detach(DynamicArray *dArray) {
    assert(dArray->size > 0);
    if (dArray->size < dArray->capacity / 4) {
        downSize(dArray);
    }
    return(dArray->array[--dArray->size]);
}

int pretach(DynamicArray *dArray) {
    assert(dArray->size > 0);
    if (dArray->size < dArray->capacity / 4) {
        downSize(dArray);
    }
    int out = dArray->array[0];
    dArray->size--;
    for (int i = 0; i < dArray->size; i++) {
        dArray->array[i] = dArray->array[i + 1];
    }
    return(out);
}

void insert(DynamicArray *dArray, int index, int item) {
    assert(index >= 0 & index < dArray->size);
    if (dArray->size == dArray->capacity) {
        upSize(dArray);
    }
    for (int i = dArray->size; i > index; i--) {
        dArray->array[i] = dArray->array[i - 1];
    }
    dArray->array[index] = item;
    dArray->size++;
}

int delete(DynamicArray *dArray, int index) {
    assert(index >= 0 & index < dArray->size);
    if (dArray->size < dArray->capacity / 4) {
        downSize(dArray);
    }
    int out = dArray->array[index];
    dArray->size--;
    for (int i = index; i < dArray->size; i++) {
        dArray->array[i] = dArray->array[i + 1];
    }
    return(out);
}

int peek(DynamicArray *dArray, int index) {
    assert(index >= 0 & index < dArray->size);
    return(dArray->array[index]);
}

void poke(DynamicArray *dArray, int index, int item) {
    assert(index >= 0 & index < dArray->size);
    dArray->array[index] = item;
}

#endif
