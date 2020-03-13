#include <iostream>
using namespace std;

void int_part(float n) {
	printf_s("%d rub. ", (int)n);
}

void float_part(float n) {
	n = n - (int)n;
	float k;
	k = n * 100;
	printf_s("%d kop", (int)roundf(k));
}

float check()
{
	float a;
	while (!scanf_s("%f", &a))
	{
		rewind(stdin);
		printf("It is not money. Try again: ");
	}
	return a;
}

int main() {
	float number;
	printf("Enter money\n");
	number = check();
	int_part(number);
	float_part(number);
	return 0;
}