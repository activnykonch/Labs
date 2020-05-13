#pragma once
#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <string.h>

typedef struct _st_node {
	void* pPrev;
	char data[100];
}Stnode;

typedef struct _stack {
	void* tail;
	unsigned int size;
}Stack;

void initialize(Stnode* p, char* data) {
	strcpy(p->data, data);
	p->pPrev = NULL;
}

void stack_init(Stack* s) {
	s->tail = NULL;
	s->size = 0;
}

void pop(Stack* s) {
	Stnode* temp = (Stnode*)s->tail;
	s->tail = ((Stnode*)s->tail)->pPrev;
	free(temp);
	s->size--;
}

void push(Stack* s, char* data) {
	Stnode* temp = (Stnode*)malloc(sizeof(Stnode));
	strcpy(temp->data, data);
	temp->pPrev = s->tail;
	s->tail = temp;
	s->size++;
}

char* peek(Stack* s) {
	if (s->size) {
		return ((Stnode*)s->tail)->data;
	}
	else return 0; //exception
}

void stack_destructor(Stack* s) {
	while (s->size) pop(s);
	free(s);
}
#endif