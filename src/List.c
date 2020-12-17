/*
 * Copyright (c) 2020,
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
 * Created : 2020 Dec 16 10:46:43
 * Last modified: 2020 Dec 16 17:55:34
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
  int value;
  struct ListNode *next;
} ListNode_t;

typedef struct List {
  int size;
  ListNode_t *head, *tail;
} List_t;

ListNode_t *ListNode_create(int value, ListNode_t *next) {
  ListNode_t *newListNode = calloc(1, sizeof(ListNode_t));
  newListNode->value = value;
  newListNode->next = next;
  return newListNode;
}

void ListNode_destroy(ListNode_t *listNode) {
  listNode->next = NULL;
  free(listNode);
}

List_t *List_create() {
  List_t *newList = calloc(1, sizeof(List_t));
  newList->head = newList->tail = NULL;
  return newList;
}

int List_indexOf(List_t *list, int value) {
  assert(list != NULL);
  ListNode_t *temp = list->head;
  int index = 0;
  while (temp != NULL && index < list->size) {
    if (temp->value == value)
      return index;
    temp = temp->next;
    ++index;
  }
  return -1;
}

int List_contains(List_t *list, int value) {
  return List_indexOf(list, value) != -1;
}

int List_getElementAt(List_t *list, int index) {
  assert(index < list->size);
  ListNode_t *temp = list->head;
  while (index) {
    temp = temp->next;
    --index;
  }
  return temp->value;
}

void List_prepend(List_t *list, int value) {
  assert(list != NULL);
  if (list->size == 0) {
    list->head = list->tail = ListNode_create(value, NULL);
  } else {
    list->head = ListNode_create(value, list->head);
  }
  ++list->size;
}

void List_append(List_t *list, int value) {
  assert(list != NULL);
  if (list->size == 0) {
    list->head = list->tail = ListNode_create(value, NULL);
  } else {
    list->tail->next = ListNode_create(value, NULL);
    list->tail = list->tail->next;
  }
  ++list->size;
}

void List_removeFront(List_t *list) {
  assert(list != NULL);
  if (list->size == 0)
    return;
  ListNode_t *temp = list->head;
  list->head = temp->next;
  ListNode_destroy(temp);
  if (list->head == NULL)
    list->tail = NULL;
  --list->size;
}

void List_removeBack(List_t *list) {
  assert(list != NULL);
  if (list->size == 0)
    return;
  ListNode_t *temp = list->head;
  while (temp->next != list->tail && temp->next != NULL) {
    temp = temp->next;
  }
  ListNode_destroy(list->tail);
  list->tail = temp;
  if (temp->next == NULL) {
    list->head = list->tail = NULL;
  }
  --list->size;
}

void List_removeAt(List_t *list, int index) {
  assert(list != NULL);
  assert(index >= 0);
  if (list->size == 0 || index >= list->size)
    return;

  if (index == 0 || (index + 1) == list->size) {
    index == 0 ? List_removeFront(list) : List_removeBack(list);
    return;
  }
  --list->size;

  ListNode_t *temp = list->head;
  while (index > 1) {
    temp = temp->next;
    --index;
  }
  ListNode_t *temp2 = temp->next;
  temp->next = temp2->next;
  ListNode_destroy(temp2);
}

void List_destroy(List_t *list) {
  assert(list != NULL);
  while (list->size != 0)
    List_removeFront(list);
  free(list);
}

void List_foreach(List_t *list, void (*Func)(const int, const int)) {
  assert(list != NULL);
  if (list->size == 0)
    return;
  ListNode_t *temp = list->head;
  while (temp != NULL) {
    Func(temp->value, temp->next == NULL);
    temp = temp->next;
  }
}

int List_size(List_t *list) {
  assert(list != NULL);
  return list->size;
}

void printer(const int i, const int isLast) {
  if (!isLast)
    printf("[%d] --> ", i);
  else
    printf("[%d]\n", i);
}

void List_tests() {
  List_t *list = List_create();
  assert(List_size(list) == 0);
  List_append(list, 10);
  assert(List_getElementAt(list, 0) == 10);
  List_prepend(list, 100);
  assert(List_size(list) == 2);
  List_removeFront(list);
  assert(List_getElementAt(list, 0) == 10);
  assert(List_size(list) == 1);
  List_append(list, 200);
  List_prepend(list, 5);
  assert(List_size(list) == 3);
  assert(List_indexOf(list, 100) == -1);
  assert(List_indexOf(list, 200) == 2);
  List_removeAt(list, 1);
  List_foreach(list, printer);
  assert(List_getElementAt(list, 1) == 200);
}

int main() { List_tests(); }
