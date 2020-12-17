/*
 * Copyright (c) 2020, jumbuna <jacobwangoni@yahoo.com>
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Created : 2020 Dec 16 22:48:17
 * Last modified: 2020 Dec 17 00:36:44
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define Vector_Full(V) V->size >= (V->capacity * .67)

#define Vector_Resize(V)                                                       \
  V->capacity *= 2;                                                            \
  V->array = realloc(V->array, V->capacity);

typedef struct Vector {
  int capacity;
  int size;
  int *array;
} Vector_t;

Vector_t *Vector_create(int capacity) {
  Vector_t *newVector = calloc(1, sizeof(Vector_t));
  newVector->capacity = capacity < 16 ? 16 : capacity;
  return newVector;
}

void Vector_destroy(Vector_t *vector) {
  assert(vector != NULL);
  free(vector->array);
  free(vector);
}

void Vector_allocateArray(Vector_t *vector) {
  vector->array = malloc(vector->capacity * sizeof(int));
}

void Vector_insert(Vector_t *vector, int value) {
  assert(vector != NULL);
  if (vector->array == NULL)
    Vector_allocateArray(vector);
  vector->array[vector->size++] = value;
  if (Vector_Full(vector)) {
    Vector_Resize(vector);
  }
}

int Vector_indexof(Vector_t *vector, int value) {
  for (int x = 0; x < vector->size; x++) {
    if (vector->array[x] == value)
      return x;
  }
  return -1;
}

int Vector_Contains(Vector_t *vector, int value) {
  return Vector_indexof(vector, value) != -1;
}

int Vector_elementAt(Vector_t *vector, int index) {
  assert(index < vector->size);
  return vector->array[index];
}

void Vector_removeAt(Vector_t *vector, int index) {
  assert(vector != NULL);
  assert(index < vector->size);
  assert(index >= 0);
  for (int i = index; i < vector->size; i++) {
    vector->array[i] = (vector->array[i + 1]);
  }
  --vector->size;
}

void Vector_remove(Vector_t *vector, int value) {
  assert(vector != NULL);
  int index = Vector_indexof(vector, value);
  if (index == -1)
    return;
  Vector_removeAt(vector, index);
}

void Vector_clean(Vector_t *vector) { vector->size = 0; }

void Vector_foreach(Vector_t *vector, void (*Func)(const int, const int)) {
  for (int i = 0; i < vector->size; i++) {
    Func(vector->array[i], i + 1 == vector->size);
  }
}

int Vector_size(Vector_t *vector) { return vector->size; }

void Vector_tests() {
  Vector_t *vector = Vector_create(16);
  assert(vector->capacity == 16 && vector->size == 0);
  Vector_insert(vector, 10);
  assert(Vector_elementAt(vector, Vector_indexof(vector, 10)) == 10);
  Vector_insert(vector, 20);
  Vector_insert(vector, 30);
  Vector_insert(vector, 40);
  Vector_insert(vector, 50);
  assert(Vector_size(vector));
  Vector_remove(vector, 20);
  assert(Vector_indexof(vector, 20) == -1);
  assert(Vector_indexof(vector, 50) == 3);
  assert(Vector_size(vector) == 4);
  Vector_clean(vector);
  assert(Vector_size(vector) == 0);
}

int main() { Vector_tests(); }
