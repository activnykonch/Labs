#pragma once
#ifndef TREE_H
#define TREE_H
#include <stdlib.h>

typedef struct _node {
	void* left;
	void* right;
	void* middle;
	int key;
}Node;

typedef struct _tree {
	void* root;
}Tree;

void node_init(Node* n, int key);

void tree_init(Tree* tr);

void add_node(Tree* tr, int key);

Node* find_node(Tree* tr, int key);

void delete_tree(Tree* tr);

void _delete_tree(Node* localroot);

void count(Node* n, int* a, int level);
#endif