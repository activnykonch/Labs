#include "tree.h"

void node_init(Node* n, int key) {
	n->left = n->right = n->middle = NULL;
	n->key = key;
}

void tree_init(Tree* tr) {
	tr->root = NULL;
}

void add_node(Tree* tr, int key) {
	if (tr->root == NULL) {
		tr->root = (Node*)malloc(sizeof(Node));
		node_init(tr->root, key);
	}
	else {
		Node* cur = tr->root;
		while (1) {
			if (key < cur->key) {
				if (cur->left == NULL) {
					cur->left = (Node*)malloc(sizeof(Node));
					node_init(cur->left, key);
					break;
				}
				else {
					cur = cur->left;
					continue;
				}
			}

			if (key > cur->key) {
				if (cur->right == NULL) {
					cur->right = (Node*)malloc(sizeof(Node));
					node_init(cur->right, key);
					break;
				}
				else {
					cur = cur->right;
					continue;
				}
			}

			if (key = cur->key) {
				if (cur->middle == NULL) {
					cur->middle = (Node*)malloc(sizeof(Node));
					node_init(cur->middle, key);
					break;
				}
				else {
					cur = cur->middle;
					continue;
				}
			}
		}
	}
}

Node* find_node(Tree* tr, int key){
	Node* current = tr->root;
	if (current != NULL) {
		while (current->key != key) {

			if (key < current->key)
				current = current->left;

			if (key > current->key)
				current = current->right;

			if (current == NULL)
				return NULL;
		}
	}
	return current;
}

void _delete_tree(Node* localroot){
	if (localroot == NULL) {
		return;
	}
	_delete_tree(localroot->left);
	_delete_tree(localroot->middle);
	_delete_tree(localroot->right);
	free(localroot);
}

void delete_tree(Tree* tr){
	Node* localroot = tr->root;
	_delete_tree(localroot);
	if (localroot == tr->root) {
		tr->root = NULL;
	}
	free(tr);
}

void count(Node* n, int* a, int level) {
	if (n == NULL) return;
	a[level] += 1;
	if (n->left) count(n->left, a, level + 1);
	if (n->middle) count(n->middle, a, level + 1);
	if (n->right) count(n->right, a, level + 1);
}
