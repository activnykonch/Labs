#pragma once
#ifndef STACK_H
#define STACK_H
#include <stdlib.h>

typedef struct _node {
	void* pPrev;
	int data;
}Node;

typedef struct _stack {
	void* tail;
	unsigned int size;
}Stack;

void initialize(Node* p, int data) {
	p->data = data;
	p->pPrev = NULL;
}

void stack_init(Stack* s) {
	s->tail = NULL;
	s->size = 0;
}

void pop(Stack* s) {
	Node* temp = (Node*)s->tail;
	s->tail = ((Node*)s->tail)->pPrev;
	free(temp);
	s->size--;
}

void push(Stack* s, int data) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->pPrev = s->tail;
	s->tail = temp;
	s->size++;
}

int peek(Stack* s) {
	if (s->size) {
		return ((Node*)s->tail)->data;
	}
	else return 0; //exception
}

void stack_destructor(Stack* s) {
	while (s->size) pop(s);
	free(s);
}
#endif