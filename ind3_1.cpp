#include <stdio.h>
int input_check()
{
	int check;
	for (int i = 0; i < 1; ++i) {
		if (scanf_s("%d", &check) != 1) {
			printf("Invalid input.Try again.\n");
			scanf_s("%*[^\n]");
			--i;
		}
	}
	return check;
}
int main() {
	int base;
	printf("Enter base of the number\n");
	base = input_check();
	int power;
	printf("Enter power of the number\n");
	power = input_check();
	int a[1000] = { 0 };
	a[1] = 1;
	int temp = 0;
	for (int b = 0; b < power; b++) {
		for (int i = 1; i < 1000; i++) {
			a[i] = a[i] * base + temp;
			if (a[i] > 9) {
				temp = a[i] / 10;
				a[i] %= 10;
			}
			else temp = 0;
		}
	}
	int counter = 999;
	int size = 0;
	while (a[counter] == 0) {
		size++;
		counter--;
	}
	size = 1000 - size;
	a[0] = size;
	for (int i = 1; i < size; i++, size--) {
		temp = a[i];
		a[i] = a[size-1];
		a[size - 1] = temp;
	}
	printf("Number of digits %d\nResult is\n", a[0]);
	for (int i = 1; i < a[0]; i++) {
		printf("%d", a[i]);
	}
	return 0;
}