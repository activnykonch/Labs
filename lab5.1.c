#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <Windows.h>
#include "stack.h"

Stack* stack_reverse(Stack* s) {
	Stack* temp = (Stack*)malloc(sizeof(Stack));
	stack_init(temp);
	while (s->size) {
		push(temp, peek(s));
		pop(s);
	}
	stack_destructor(s);
	return temp;
}

int main()
{
	Stack* st = (Stack*)malloc(sizeof(Stack));
	stack_init(st);
	int a;
	a = 0;
	while (1) {
		a = _getch();
		if (a == 13) break;
		printf("%c", a);
		push(st, a);
	}
	system("cls");
	st = stack_reverse(st);
	while (st->size) {
		a = peek(st);
		printf("%c", a);
		pop(st);
	}
	stack_destructor(st);
	return 0;
}