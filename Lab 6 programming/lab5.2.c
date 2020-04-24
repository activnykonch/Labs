#include <stdio.h>
#include <conio.h>
#include "tree.h"

void show(Node* n) {
	if (n != NULL) {
		show(n->left);
		show(n->middle);
		printf("%d ", n->key);
		show(n->right);
	}
}

int check()
{
	int a;
	while (!scanf_s("%d", &a))
	{
		rewind(stdin);
		printf("Incorrect input. Try again: ");
	}
	return a;
}

int main()
{
	Tree* tr = (Tree*)malloc(sizeof(Tree));
	tree_init(tr);
	printf("How many nodes you want to add?\n");
	int amount, x;
	amount = check();
	printf("Enter elemts of your tree\n");
	while (amount) {
		x = check();
		add_node(tr, x);
		amount--;
	}
	system("cls");
	printf("Your tree:\n");
	show(tr->root);
	int a[50] = { 0 }, level = 0;
	count(tr->root, a, level);
	while (a[level] != 0) {
		printf("\nLevel %d contains %d node(s)", level, a[level]);
		level++;
	}
	printf("\nTree has %d levels", level);
	delete_tree(tr);
	_getch();
}
