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
 * Created : 2020 Dec 19 07:49:42
 * Last modified: 2020 Dec 19 10:20:53
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct DListNode {
  int value;
  struct DListNode *next, *prev;
} DListNode_t;

typedef struct DList {
  int size;
  DListNode_t *head, *tail;
} DList_t;

DListNode_t *DListNode_create(DListNode_t *next, DListNode_t *prev, int value) {
  DListNode_t *newNode = calloc(1, sizeof(DListNode_t));
  newNode->value = value;
  newNode->prev = prev;
  newNode->next = next;
  if (prev != NULL)
    prev->next = newNode;
  if (next != NULL)
    next->prev = newNode;
  return newNode;
}

void DListNode_destroy(DListNode_t *node) {
  node->next = node->prev = NULL;
  free(node);
}

DList_t *DList_create() {
  DList_t *newList = calloc(1, sizeof(DList_t));
  return newList;
}

void DList_insertFront(DList_t *list, int value) {
  assert(list != NULL);
  if (list->size == 0) {
    list->head = list->tail = DListNode_create(NULL, NULL, value);
  } else {
    list->head = DListNode_create(list->head, NULL, value);
  }
  ++list->size;
}

void DList_insertBack(DList_t *list, int value) {
  assert(list != NULL);
  if (list->size == 0) {
    list->head = list->tail = DListNode_create(NULL, list->tail, value);
  } else {
    list->tail = DListNode_create(NULL, list->tail, value);
  }
  ++list->size;
}

int DList_indexof(DList_t *list, int value) {
  assert(list != NULL);
  if (list->size > 0) {
    int index = 0;
    DListNode_t *temp = list->head;
    while (temp != NULL) {
      if (temp->value == value)
        return index;
      else {
        temp = temp->next;
        index++;
      }
    }
  }
  return -1;
}

int DList_contains(DList_t *list, int value) {
  return DList_indexof(list, value) != -1;
}

DListNode_t *DList_getNodeAt(DList_t *list, int index) {
  assert(list != NULL);
  assert(list->size > index);
  assert(index > -1);
  DListNode_t *temp = list->head;
  while (index > 0) {
    temp = temp->next;
    index--;
  }
  return temp;
}

int DList_valueAt(DList_t *list, int index) {
  return DList_getNodeAt(list, index)->value;
}

void DList_removeFront(DList_t *list) {
  assert(list != NULL);
  if (list->size == 0)
    return;
  DListNode_t *temp = list->head;
  list->head = temp->next;
  if (list->size > 1)
    list->head->prev = NULL;
  DListNode_destroy(temp);
  --list->size;
}

void DList_removeBack(DList_t *list) {
  assert(list != NULL);
  if (list->size == 0)
    return;
  DListNode_t *temp = list->tail;
  list->tail = temp->prev;
  DListNode_destroy(temp);
  if (list->size > 1)
    list->tail->next = NULL;
  --list->size;
}

void DList_removeAt(DList_t *list, int index) {
  if (index == 0 || index == 1) {
    index == 0 ? DList_removeFront(list) : DList_removeBack(list);
    return;
  }
  DListNode_t *temp = DList_getNodeAt(list, index);
  temp->next->prev = temp->prev;
  temp->prev->next = temp->next;
  --list->size;
}

void DList_forEach(DList_t *list, void (*Func)(const int, const int)) {
  assert(list != NULL);
  if (list->size == 0)
    return;
  DListNode_t *temp = list->head;
  while (temp->next != NULL) {
    Func(temp->value, 0);
  }
  Func(temp->value, 1);
}

void DList_destroy(DList_t *list) {
  assert(list != NULL);
  while (list->size > 0) {
    DList_removeFront(list);
  }
  free(list);
}

int DList_size(DList_t *list) {
  assert(list != NULL);
  return list->size;
}

void DList_tests() {
  DList_t *list = NULL;
  list = DList_create();
  assert(list != NULL);
  assert(DList_size(list) == 0);
  DList_insertFront(list, 10);
  DList_insertBack(list, 32);
  assert(list->size == 2);
  assert(DList_valueAt(list, 1) == 32);
  DList_insertFront(list, 60);
  DList_insertFront(list, 16);
  DList_removeFront(list);
  assert(!DList_contains(list, 16));
  assert(DList_size(list) == 3);
  DList_removeBack(list);
  assert(DList_size(list) == 2);
  assert(!DList_contains(list, 32));
  DList_insertFront(list, 2);
  DList_removeAt(list, 1);
  assert(DList_indexof(list, 10) == -1);
  DList_destroy(list);
}

int main() { DList_tests(); }
