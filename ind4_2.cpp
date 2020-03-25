#include <stdio.h>
#include <string.h>
#include <ctype.h>
void dots(char a[][50], int* n) {
	for (int i = 0; i < *n; i++) {
		if (a[i][0] == '.' && a[i + 1][0] == '.' && a[i + 2][0] == '.') {
			for (int j = 0; j < 3; j++) {
				a[i][j] = '.';
			}
			a[i][3] = '\0';
			for (int k = 0; k < 2; k++)
				for (int j = i + 1; j < *n; j++) {
					if (j == *n - 1) *n = *n - 1;
					else strcpy(a[j], a[j + 1]);
				}
		}
	}
}
int check_a(char ch) {
	char a_sym[] = { '.', ',', ';', ':', '!', '?', ')', ']', ']', '\0'};
	for (int k = 0; k < strlen(a_sym); k++) if (a_sym[k] == ch) {
		return  1;
		break;
	}
	return 0;
}
int check_b(char ch) {
	char b_sym[] = { '(', '[', '{', '\0' };
	for (int k = 0; k < strlen(b_sym); k++) if (b_sym[k] == ch) { 
		return  1;
		break; 
	}
	return 0;
}
void after(char a[][50], int* n) {
	for (int i = 0; i < *n; i++) {
		if (check_a(a[i][0])) {
			if (!isspace(a[i + 1][0])) {
				*n = *n + 1;
				for (int j = *n - 2; j >= i + 1; j--) {
					strcpy(a[j + 1], a[j]);
				}
				a[i + 1][0] = ' ';
				a[i + 1][1] = '\0';
			}
		}
	}
}
void before(char a[][50], int* n) {
	for (int i = 1; i < *n; i++) {
		if (check_b(a[i][0])) {
			if (!isspace(a[i - 1][0])) {
				*n = *n + 1;
				for (int j = *n - 2; j >= i - 1; j--) {
					strcpy(a[j + 1], a[j]);
				}
				a[i][0] = ' ';
				a[i][1] = '\0';
				i++;
			}
		}
	}
}
int main() {
	FILE* fp;
	fp = fopen("text.txt", "r");
	if (fp == NULL) {
		printf("File is not found");
		exit(1);
	}
	int words = 0;
	char text[80][50];
	while (!feof(fp)) {
		for (int j = 0; j < 50; j++) {
			char ch = fgetc(fp);
			if (feof(fp)) { text[words][j] = '\0'; break; }
			if (check_a(ch) || check_b(ch) || ch==' ') {
				if (j != 0) {
					text[words][j] = '\0';
					text[words + 1][0] = ch;
					text[words + 1][1] = '\0';
					words++;
					break;
				}
				else {
					text[words][0] = ch;
					text[words][1] = '\0';
				}
			}
			else text[words][j] = ch;
		}
		words++;
	}
	fclose(fp);
	printf("Text:\n");
	for (int i = 0; i < words; i++)
		for (int j = 0; j < strlen(text[i]); j++) putchar(text[i][j]);
	dots(text, &words);
	before(text, &words);
	after(text, &words);
	printf("\nEdited text:\n");
	for (int i = 0; i < words; i++)
		for (int j = 0; j < strlen(text[i]); j++) putchar(text[i][j]);
	fp = fopen("edited_text.txt", "w");
	if (fp == NULL) {
		printf("File is not found");
		exit(1);
	}
	for (int i = 0; i < words; i++)
		for (int j = 0; j < strlen(text[i]); j++) fputc(text[i][j], fp);
	fclose(fp);
	return 0;
}
