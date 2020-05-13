#include <conio.h>
#include <stdio.h>
#include <string.h>
#include "List.h"
#include "stack.h"

#define mingrant 78.862
#define raisedgrant 94.634
#define secraisedgrant 110.405
#define maxgrant 126.179
#define counsilsgrant 135.000
#define specialgrant 181.000

char path[] = { "database.txt" };
char sheet[] = { "sheet.txt" };


void separate_strings(Stack* st, char* str, char separator);
void fill_database(List* lst);
void fill_student(Student* stud, Stack* st);
void add_student(List* lst);
void delete_student(List* lst);
void edit_student_data(List* lst);
void show_student_data(Student* stud, char option);
void write_students_base(List* lst);
void write_grants_base(List* lst);
void print_database(List* lst);
void menu(List* lst);
void calculate_grants(List* lst);
void calculate_by_score(List* lst);
void pay_counsil_grant(List* lst);
void pay_named_grant(List* lst);
void print_sheet(List* lst);

int main() {
	List* studentsbase = (List*)malloc(sizeof(List));
	list_contructor(studentsbase);
	fill_database(studentsbase);
	menu(studentsbase);
	_getch();
	return 0;
}

void separate_strings(Stack* st, char* str, char separator) {
	for (int i = 0; i < strlen(str); i++) {
		char temp[100] = { 0 };
		int j = 0;
		while (str[i] != separator && i < strlen(str)) {
			if (str[i] == '\n') break;
			temp[j] = str[i];
			j++;
			i++;
		}
		temp[j] = '\0';
		push(st, temp);
	}
}

void fill_database(List* lst) {
	FILE* fp;
	if (fp = fopen(path, "r")) {
		while (!feof(fp)) {
			char buffer[100] = { 0 };
			fgets(buffer, 100, fp);
			Stack* st = (Stack*)malloc(sizeof(Stack));
			stack_init(st);
			separate_strings(st, buffer, ' ');
			if (st->size) {
				Student* stud = (Student*)malloc(sizeof(Student));
				fill_student(stud, st);
				push_back(lst, stud);
			}
			free(st);
		}
		fclose(fp);
	}
	else {
		system("cls");
		printf("FILE NOT FOUND");
	}
}

void fill_student(Student* stud, Stack* st) {
	stud->score = strtof(peek(st), NULL);
	pop(st);
	strcpy(stud->educform, peek(st));
	pop(st);
	strcpy(stud->secondname, peek(st));
	pop(st);
	strcpy(stud->name, peek(st));
	pop(st);
	strcpy(stud->surname, peek(st));
	pop(st);
	stud->grant = 0;
}

void add_student(List* lst) {
	system("cls");
	Student* stud = (Student*)malloc(sizeof(Student));
	char buffer[100] = { 0 };
	printf("Enter student's surname\n");
	_getch();
	gets(buffer);
	strcpy(stud->surname, buffer);
	printf("Enter student's name\n");
	_getch();
	gets(buffer);
	strcpy(stud->name, buffer);
	printf("Enter student's secondname\n");
	_getch();
	gets(buffer);
	strcpy(stud->secondname, buffer);
	printf("Enter student's form of education\n");
	_getch();
	gets(buffer);
	strcpy(stud->educform, buffer);
	printf("Enter student's score\n");
	float temp;
	scanf("%f", &temp);
	stud->score = temp;
	stud->grant = 0;
	push_back(lst, stud);
	printf("\nPress esc to main menu or 0 to add another student");
	char c = _getch();
	while (1) {
		if (c == 27) menu(lst);
		if (c == '0') add_student(lst);
	}
}

void delete_student(List* lst) {
	system("cls");
	printf("Which student you want to delete?(0 to main menu)\n");
	for (int i = 0; i < lst->size; i++) {
		Node* nd = get_node(lst, i);
		printf("%d.", i + 1);
		puts(((Student*)nd->data)->surname);
	}
	int choice;
	scanf("\n%d", &choice);
	if (choice == 0) {
		menu(lst);
		return;
	}
	delete_node(lst, choice - 1);
	printf("\nPress esc to main menu or 0 to delete another student");
	char c = _getch();
	while (1) {
		if (c == 27) {
			menu(lst);
			return;
		}
		if (c == '0') delete_student(lst);
	}
}

void edit_student_data(List* lst) {
	char m_flag = 0;
	do {
		m_flag = 0;
		system("cls");
		printf("Which student's data you want to edit?(Press 0 to main menu)\n");
		for (int i = 0; i < lst->size; i++) {
			Node* nd = get_node(lst, i);
			printf("%d.", i + 1);
			puts(((Student*)nd->data)->surname);
		}
		int choice;
		while (1) {
			scanf("%d", &choice);
			if (choice >= 1) break;
			if (choice == 0) {
				menu(lst);
				return;
			}
			rewind(stdin);
		}
		Node* temp = get_node(lst, choice - 1);
		char flag = 0;
		do {
			flag = 0;
			system("cls");
			show_student_data(temp->data, 0);
			printf("Which data you want to edit?(Press esc to main menu or 0 to choose another student)\n");
			char ch;
			while (ch = _getch()) {
				if (ch == 27) menu(lst); 
				if (ch == '0') {
					m_flag = 1;
					break;
				}
				if (ch >= '1' && ch <= '5') break;
			}
			if (m_flag) continue;
			char buffer[15];
			system("cls");
			switch (ch)
			{
			case '1':
				printf("Enter new surname:\n");
				_getch();
				gets(buffer);
				strcpy(((Student*)temp->data)->surname, buffer);
				break;
			case '2':
				printf("Enter new name:\n");
				_getch();
				gets(buffer);
				strcpy(((Student*)temp->data)->name, buffer);
				break;
			case '3':
				printf("Enter new second name:\n");
				_getch();
				gets(buffer);
				strcpy(((Student*)temp->data)->secondname, buffer);
				break;
			case '4':
				printf("Enter new form of education:\n");
				_getch();
				gets(buffer);
				strcpy(((Student*)temp->data)->educform, buffer);
				break;
			case '5':
				printf("Enter new score:\n");
				float a;
				scanf("%f", &a);
				((Student*)temp->data)->score = a;
				break;
			}
			printf("\n\nPress esc to main menu or 0 to change more data");
			while (1) {
				char c = _getch();
				if (c == 27) {
					menu(lst);
					return;
				}
				else if (c == '0') {
					flag = 1;
					break;
				}
			}
		} while (flag);

	} while (m_flag);
}

void show_student_data(Student* stud, char option) {
	if (option == 0) {
		printf("1. Surname: %s\n", stud->surname);
		printf("2. Name: %s\n", stud->name);
		printf("3. Second name: %s\n", stud->secondname);
		printf("4. Form of education: %s\n", stud->educform);
		printf("5. Score: %1.2f\n", stud->score);
	}
	if (option == 1) {
		printf("%s\t%s\t%s\t", stud->surname, stud->name, stud->secondname);
		printf("%s\t%1.2f\n", stud->educform, stud->score);
	}
}

void write_students_base(List* lst) {
	FILE* fp;
	if (fp = fopen(path, "w")) {
		for (int i = 0; i < lst->size; i++) {
			Node* nd = get_node(lst, i);
			fprintf(fp, "%s", ((Student*)nd->data)->surname);
			fputc(' ', fp);
			fprintf(fp, "%s", ((Student*)nd->data)->name);
			fputc(' ', fp);
			fprintf(fp, "%s", ((Student*)nd->data)->secondname);
			fputc(' ', fp);
			fprintf(fp, "%s", ((Student*)nd->data)->educform);
			fputc(' ', fp);
			fprintf(fp, "%1.2f", ((Student*)nd->data)->score);
			fputc('\n', fp);
		}
		fclose(fp);
	}
	else {
		system("cls");
		printf("FILE NOT FOUND");
	}
}

void write_grants_base(List* lst, int i) {
	FILE* fp;
	fp = fopen(sheet, "a");
	Node* nd = get_node(lst, i);
	fprintf(fp, "%s", ((Student*)nd->data)->surname);
	fputc(' ', fp);
	fprintf(fp, "%s", ((Student*)nd->data)->name);
	fputc(' ', fp);
	fprintf(fp, "%s", ((Student*)nd->data)->secondname);
	fputc(' ', fp);
	fprintf(fp, "%s", ((Student*)nd->data)->educform);
	fputc(' ', fp);
	fprintf(fp, "%1.2f", ((Student*)nd->data)->score);
	fputc(' ', fp);
	fprintf(fp, "%1.3f ", ((Student*)nd->data)->grant);
	fprintf(fp, "rubbles");
	fputc('\n', fp);
	fclose(fp);
}

void print_database(List* lst) {
	system("cls");
	for (int i = 0; i < lst->size; i++) {
		Node* nd = get_node(lst, i);
			printf("%d)Student's data:\n", i + 1);
			show_student_data(nd->data, 1);
	}
	printf("\nPress esc to main menu");
	char c = _getch();
	while (1) {
		if (c == 27) menu(lst);
	}
}

void menu(List* lst) {
	while (1) {
		system("cls");
		printf("Choose function to work:\n1. Add student to base\n2. Edit student's data\n");
		printf("3. Delete information about student\n4. View all list\n5. Pay grants\n6. Print sheet\n\nEsc - exit\n");
		char choice;
		while (1) {
			choice = _getch();
			if ((choice >= '0' && choice <= '6') || choice == 27) break;
		}
		switch (choice) {
		case '1':
			add_student(lst);
			break;
		case '2':
			edit_student_data(lst);
			break;
		case '3':
			delete_student(lst);
			break;
		case '4':
			print_database(lst);
			break;
		case '5':
			calculate_grants(lst);
			break;
		case '6':
			print_sheet(lst);
			break;
		case 27:
			write_students_base(lst);
			exit(0);
		}
	}
}

void calculate_grants(List* lst) {
	system("cls");
	printf("1. Pay grants by score\n2. Pay grants of students' counsil\n3. Pay special named grants\n\nEsc to main menu");
	char choice;
	while (1) {
		choice = _getch();
		if ((choice >= '1' && choice <= '3')) break;
		if (choice == 27) {
			menu(lst);
			return;
		}
	}
	switch (choice) {
	case '1':
		calculate_by_score(lst);
		break;
	case '2':
		pay_counsil_grant(lst);
		break;
	case '3':
		pay_named_grant(lst);
		break;
	}
}

void calculate_by_score(List* lst) {
	for (int i = 0; i < lst->size; i++) {
		Node* nd = get_node(lst, i);
		if (!strcmp(((Student*)nd->data)->educform, "budget")) {
			if (((Student*)nd->data)->score >= 5 && ((Student*)nd->data)->score < 6) ((Student*)nd->data)->grant += mingrant;
			if (((Student*)nd->data)->score >= 6 && ((Student*)nd->data)->score < 8) ((Student*)nd->data)->grant += raisedgrant;
			if (((Student*)nd->data)->score >= 8 && ((Student*)nd->data)->score < 9) ((Student*)nd->data)->grant += secraisedgrant;
			if (((Student*)nd->data)->score >= 9 && ((Student*)nd->data)->score <= 10) ((Student*)nd->data)->grant += maxgrant;
		}
	}
}

void pay_counsil_grant(List* lst) {
	char flag = 0;
	do {
		flag = 0;
		system("cls");
		printf("Which student deserved students' counsil's grant(0 to main menu)\n");
		for (int i = 0; i < lst->size; i++) {
			Node* nd = get_node(lst, i);
			printf("%d.", i + 1);
			puts(((Student*)nd->data)->surname);
		}
		int choice;
		while (1) {
			scanf("%d", &choice);
			if (choice == 0) {
				menu(lst);
				return;
			}
			if (choice >= 1) break;
			rewind(stdin);
		}
		Node* nd = get_node(lst, choice - 1);
		((Student*)nd->data)->grant += counsilsgrant;
		system("cls");
		printf("Grant paid\nPress esc to main menu or 0 to pay another student");
		char ch;
		while (1) {
			ch = _getch();
			if (ch == 27) {
				menu(lst);
				return;
			}
			if (ch == '0') {
				flag = 1;
				break;
			}
		}
	} while (flag);
}

void pay_named_grant(List* lst) {
	char flag = 0;
	do {
		flag = 0;
		system("cls");
		printf("Which student deserved special named grant(0 to main menu)\n");
		for (int i = 0; i < lst->size; i++) {
			Node* nd = get_node(lst, i);
			printf("%d.", i + 1);
			puts(((Student*)nd->data)->surname);
		}
		int choice;
		while (1) {
			scanf("%d", &choice);
			if (choice == 0) {
				menu(lst);
				return;
			}
			if (choice >= 1) break;
			rewind(stdin);
		}
		Node* nd = get_node(lst, choice - 1);
		((Student*)nd->data)->grant += specialgrant;
		system("cls");
		printf("Grant paid\nPress esc to main menu or 0 to pay another student");
		char ch;
		while (1) {
			ch = _getch();
			if (ch == 27) {
				menu(lst);
				return;
			}
			if (ch == '0') {
				flag = 1;
				break;
			}
		}
	} while (flag);
}

void print_sheet(List* lst) {
	system("cls");
	FILE* fp;
	fp = fopen(sheet, "w");
	printf("List of students got grants:\n\n");
	fprintf(fp, "List of students got grants:\n\n");
	fclose(fp);
	float sum = 0;
	for (int i = 0; i < lst->size; i++) {
		Node* nd = get_node(lst, i);
			if (((Student*)nd->data)->grant) {
				write_grants_base(lst, i);
				sum += ((Student*)nd->data)->grant;
				printf("%s %s %s ", ((Student*)nd->data)->surname, ((Student*)nd->data)->name, ((Student*)nd->data)->secondname);
				printf("%s %1.2f %1.3f rubbles\n", ((Student*)nd->data)->educform, ((Student*)nd->data)->score, ((Student*)nd->data)->grant);
			}
	}
	fp = fopen(sheet, "a");
	printf("\nList of students got raised grants:\n\n");
	fprintf(fp, "\nList of students got raised grants:\n\n");
	fclose(fp);
	for (int i = 0; i < lst->size; i++) {
		Node* nd = get_node(lst, i);
		if (((Student*)nd->data)->score >= 6.00 && ((Student*)nd->data)->grant) {
			write_grants_base(lst, i);
			printf("%s %s %s ", ((Student*)nd->data)->surname, ((Student*)nd->data)->name, ((Student*)nd->data)->secondname);
			printf("%s %1.2f %1.3f rubbles\n", ((Student*)nd->data)->educform, ((Student*)nd->data)->score, ((Student*)nd->data)->grant);
		}
	}

	fp = fopen(sheet, "a");
	printf("\nTotally paid %1.3f rubbles\n", sum);
	fprintf(fp, "\nTotally paid %1.3f rubbles\n", sum);
	fclose(fp);

	printf("\nPress ecs to main menu");
	char c;
	while (1) {
		c = _getch();
		if (c == 27) {
			menu(lst);
			return;
		}
	}
} //изменить печать ведомости в файл