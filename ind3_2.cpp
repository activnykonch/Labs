#include <iostream>
int input_check();
int main() {
	int width;
	int height;
	int velocity;
	int exit;
	int counter = 0;
	do {
		counter++;
		printf("Enter width[%d]\n", counter);
		width = input_check();
		printf("Enter height[%d]\n", counter);
		height = input_check();
		printf("Enter velocity[%d]\n", counter);
		velocity = input_check();
		printf("River rate[%d] is %d m^3/s\n", counter, width * height * velocity);
		printf("Press 1 to continue or 0 to exit\n");
		exit = input_check();
	} while (exit != 0);
	return 0;
}

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