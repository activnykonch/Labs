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

void initialize(Node* p, int data);

void stack_init(Stack* s);

void pop(Stack* s);

void push(Stack* s, int data);

int peek(Stack* s);

void stack_destructor(Stack* s);
#endif