#pragma once
#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

typedef struct _students_databàse {
	char name[15];
	char surname[15];
	char secondname[15];
	char educform[15];
	float score;
	float grant;
}Student;

typedef struct _list {
	void* head;
	void* tail;
	int size;
}List;

typedef struct _node {
	void* pnext;
	void* pprev;
	void* data;
}Node;

void list_contructor(List* lst) {
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
}

void push_back(List* lst, Student* data) {
	Node* nd = (Node*)malloc(sizeof(Node));
	nd->data = data;
	nd->pnext = NULL;
	nd->pprev = lst->tail;
	if (lst->tail)
		((Node*)lst->tail)->pnext = nd;
	lst->tail = nd;
	if (!lst->head) lst->head = nd;
	lst->size++;
}

void push_front(List* lst, Student* data) {
	Node* nd = (Node*)malloc(sizeof(Node));
	nd->data = data;
	nd->pprev = NULL;
	nd->pnext = lst->head;
	if (lst->head)
		((Node*)lst->head)->pprev = nd;
	lst->head = nd;
	if (!lst->tail)
		lst->tail = nd;
	lst->size++;
}

void pop_back(List* lst) {
	if (lst->size) {
		Node* temp = (Node*)lst->tail;
		lst->tail = temp->pprev;
		free(temp);
		lst->size--;
	}
}

void pop_front(List* lst) {
	if (lst->size) {
		Node* temp = (Node*)lst->head;
		lst->head = temp->pnext;
		free(temp);
		lst->size--;
	}
}

Node* get_node(List* lst, int index) {
	Node* nd = NULL;
	int i;
	if (index < lst->size / 2) {
		nd = (Node*)lst->head;
		i = 0;
		while (nd && i < index) {
			nd = (Node*)nd->pnext;
			i++;
		}
	}
	else {
		nd = (Node*)lst->tail;
		i = lst->size - 1;
		while (nd && i > index) {
			nd = (Node*)nd->pprev;
			i--;
		}
	}
	return nd;
}

void insert_node(List* lst, int index, Student* data) {
	if (index == 0) push_front(lst, data);
	else if (index == lst->size) push_back(lst, data);
	else {
		Node* ins = NULL;
		Node* nd = get_node(lst, index);
		if (nd) {
			ins = (Node*)malloc(sizeof(Node));
			ins->data = nd->data;
			ins->pprev = nd;
			ins->pnext = nd->pnext;
			if (nd->pnext) {
				((Node*)nd->pnext)->pprev = ins;
			}
			nd->pnext = ins;

			if (!nd->pprev) {
				lst->head = nd;
			}
			if (!nd->pnext) {
				lst->tail = nd;
			}
			lst->size++;
		}
	}
}

void delete_node(List* lst, int index) {
	Node* nd = get_node(lst, index);
	if (nd) {
		if (nd->pnext) {
			((Node*)nd->pnext)->pprev = nd->pprev;
		}
		if (nd->pprev) {
			((Node*)nd->pprev)->pnext = nd->pnext;
		}

		if (!nd->pprev) {
			lst->head = nd->pnext;
		}
		if (!nd->pnext) {
			lst->tail = nd->pprev;
		}
		free(nd);
		lst->size--;
	}
}

void clear_list(List* lst) {
	while (lst->size) {
		pop_front(lst);
	}
}

void list_destructor(List* lst) {
	clear_list(lst);
	free(lst);
}
#endif