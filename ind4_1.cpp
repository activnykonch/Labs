#include <stdio.h>
#include <string.h>
#include <ctype.h>
void check_words(char a[][50], int* n) {
	for (int i = 0; i < *n - 2; i++) {
		int flag = 0;
		if (isalpha(a[i][0]) && isalpha(a[i + 2][0])) {
			if (islower(a[i][0])) {
				if (!islower(a[i + 2][0])) {
					a[i + 2][0] = tolower(a[i + 2][0]);
					flag = 1;
				}
			}
			else if (islower(a[i + 2][0])) {
				a[i + 2][0] = toupper(a[i + 2][0]);
				flag = 1;
			}
			if (!strcmp(a[i], a[i + 2])) {
				if (strstr(a[i], a[i + 2])) {
					for (int k = 0; k < 2; k++)
						for (int j = i + 1; j < *n; j++) {
							if (j == *n - 1) *n = *n - 1;
							else strcpy(a[j], a[j + 1]);
						}
				}
			}
			else if (flag == 1)
					if (islower(a[i + 2][0])) a[i + 2][0] = toupper(a[i + 2][0]);
					else a[i + 2][0] = tolower(a[i + 2][0]);
		}
	}
}
void check_reg(char a[][50], int* n) {
	for (int i = 0; i < *n; i++) {
		if (a[i][0] == '.' && isalpha(a[i + 1][0])) {
			if (!isspace(a[i + 1][0])) {
				*n = *n + 1;
					for (int j = *n - 2; j >= i + 1; j--) {
						strcpy(a[j + 1], a[j]);
					}
				a[i + 1][0] = ' ';
				a[i + 1][1] = '\0';
			}
			if (islower(a[i + 2][0])) a[i + 2][0] = toupper(a[i + 2][0]);
		}
	}
}
int main() {
	char text[80][50];
	int counter=0;
	printf("Input text\n");
	for (int i = 0; i < 50; i++) {
		counter++;
		for (int j = 0; j < 50; j++) {
 			char ch = getchar();
			if (ch == ' ' || ch==',' || ch=='.' || ch=='!' || ch=='?') {
				if(j!=0) text[i][j] = '\0';
				text[i + 1][0] = ch;
				text[i + 1][1] = '\0';
				i++;
				counter++;
				break;
			}
			else if (ch == '\n') {
				text[i][j] = '\0';
 				i = 50;
				break;
			}
			else text[i][j] = ch;
		}
	}
	check_words(text, &counter);
	check_reg(text, &counter);
	printf("Edited variant\n");
	for (int i = 0; i < counter; i++) {
		 printf(text[i]);
	}
	return 0;
}
//This this stupid text fucked my brain.sorry god