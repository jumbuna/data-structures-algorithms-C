#include <stdlib.h>
#include <stdio.h>

struct node {
	int data;
	struct node *next;
};

struct list {
	struct node *head, *tail;
	int size;
};

struct list *newList() {
	struct list *list = (struct list *) malloc(sizeof(struct list));
	list->head = list->tail = 0;
	list->size = 0;
	return list;
}

void clearList(struct list *list) {
	if(list->size > 0) {
		struct node *temp;
		while(list->head != 0) {
			temp = list->head;
			list->head = list->head->next;
			free(temp);
		}
		list->size = 0;
	}
}

void freeList(struct list *list) {
	clearList(list);
	free(list);
}

void insertFront(struct list *list, int val) {
	struct node *newNode = (struct node *) malloc(sizeof(struct node));
	newNode->next = list->head;
	newNode->data = val;
	if(list->size == 0) {
	 	list->head = list->tail = newNode;
	} else {
		list->head = newNode; 
	}
	++(list->size);
}

void insertBack(struct list *list, int val) {
	struct node *newNode = (struct node *) malloc(sizeof(struct node));
	newNode->data = val;
	newNode->next = 0;
	if(list->size == 0) {
		list->head = list->tail = newNode;
	} else {
		list->tail->next = newNode;
		list->tail = newNode;
	}
	++(list->size);
}

void printList(struct list *list) {
	struct node *temp = list->head;
	while(temp != 0) {
		printf("%d, ", temp->data);
		temp = temp->next;
	}
}


static struct node* reverse(struct node *nod) {
	if(nod->next == 0) {
		return nod;
	}
	reverse(nod->next)->next = nod;
	return nod;
}

void reverseList(struct list *list) {
	if(list->size > 0) {
		struct node *t = list->tail;
		list->tail = reverse(list->head);
		list->head = t;
		list->tail->next = 0;
	}
}

void removeFront(struct list *list) {
	if(list->size > 0) {
		struct node *temp = list->head;
		list->head = list->head->next;
		free(temp);
		--(list->size);
	}
}

void removeBack(struct list *list) {
	if(list->size > 0) {
		struct node *temp = list->head;
		while(temp->next != list->tail) {
			temp = temp->next;
		}
		free(list->tail);
		list->tail = temp;
		list->tail->next = 0;
		--(list->size);
	}
}
