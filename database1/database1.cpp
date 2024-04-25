#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef union {
	char* album;
	char* singl;
}al_sin;

typedef struct node {
	char* song_title;
	char* genre;
	char* singer_title;
	int year;
	al_sin albsin;
	struct node* next;
}node;

node* head = NULL;

char* get_string()
{
	int i = 0;
	char symbol;
	int counter = 1;
	char* string = (char*)malloc(sizeof(char));
	symbol = getchar();
	while (symbol != '\n')
	{
		string[i++] = symbol;
		if (i >= counter)
		{
			counter *= 2;
			string = (char*)realloc(string, counter * sizeof(char));
		}
		symbol = getchar();
	}
	string[i] = '\0';
	return string;
	free(string);
}

char* get_string_from_file(FILE* input)
{
	int i = 0;
	int symbol;
	int counter = 1;
	char* string = (char*)malloc(sizeof(char));
	symbol = fgetc(input);
	while (symbol != '\n')
	{
		string[i++] = symbol;
		if (i >= counter)
		{
			counter *= 2;
			string = (char*)realloc(string, counter * sizeof(char));
		}
		symbol = fgetc(input);
	}
	string[i] = '\0';
	return string;
	free(string);
}

void add_element() {
	int flag = 1;
	node* newelem = (node*)malloc(sizeof(node));
	printf("Enter genre of song:\n");
	newelem->genre = get_string();

	printf("Enter name of singer/band:\n");
	newelem->singer_title = get_string();
	
	printf("Enter title of song:\n");
	newelem->song_title = get_string();
	
	printf("Enter year:\n");
	int year;
	scanf_s("%d", &year);
	newelem->year = year;

	printf("Album or Singl:\n");
	getchar();
	while (flag)
	{
		char* string = get_string();
		if (strcmp(string, "Album") == 0)
		{
			printf("ENTER the name of the album:\n");
			char* string_album = get_string();
			newelem->albsin.album = string_album;
			flag = 0;
		}
		else if (strcmp(string, "Singl") == 0)
		{
			newelem->albsin.singl = string;
			flag = 0;
		}
		else printf("Incorrect input, please try again:\n");
	}

	newelem->next = head;
	head = newelem;

	printf("Addition is completed\n");
}

void print_base() {
	node* temporary = head;
	if (temporary == NULL) printf("Base is empty");
	else
	{
		while (temporary != NULL)
		{
			printf("Song title: %s\n", temporary->song_title);
			printf("Name of singer/band: %s\n", temporary->singer_title);
			printf("Genre: %s\n", temporary->genre);
			printf("Year: %d\n", temporary->year);
			printf("Album/Singl: %s\n", temporary->albsin);
			printf("-----------------\n");
			temporary = temporary->next;
		}
	}
}

void find_element() {
	printf("Enter the song title of element you want to find:");
	getchar();
	char* string = get_string();
	node* elem_to_find = head;
	int found = 0;
	while (elem_to_find != NULL)
	{
		if (strcmp(elem_to_find->song_title, string) == 0)
		{
			printf("Song title: %s\n", elem_to_find->song_title);
			printf("Name of singer/band: %s\n", elem_to_find->singer_title);
			printf("Genre: %s\n", elem_to_find->genre);
			printf("Year: %d\n", elem_to_find->year);
			printf("Album/Singl: %s\n", elem_to_find->albsin);
			printf("-----------------\n");
			found++;
		}
		elem_to_find = elem_to_find->next;
	}
	if (found == 0 && elem_to_find == NULL) printf("No such element or base is empty");
}

void delete_element() {
	printf("Enter the song_title of element you want to delete:");
	getchar();
	char* string = get_string();
	node* before_temporary = NULL;
	node* temporary = head;
	if (temporary == NULL) {
		printf("Base is empty"); return;
	}
	while (temporary && strcmp(temporary->song_title, string) != 0)
	{
		before_temporary = temporary;
		temporary = temporary->next;
	}
	if (temporary == head)
	{
		head = temporary->next;
		free(temporary);
		printf("Succesfully deleted");
		return;
	}
	if (!temporary)
	{
		printf("No such element");
		return;
	}
	before_temporary->next = temporary->next;
	free(temporary);
	printf("Succesfully deleted");
}

void write_to_file() {
	FILE* output;
	fopen_s(&output, "output.txt", "w");
	node* temporary = head;
	if (temporary == NULL) printf("Base is empty");
	else
	{
		while (temporary != NULL)
		{
			fprintf(output,"Song title: %s\n", temporary->song_title);
			fprintf(output, "Name of singer/band: %s\n", temporary->singer_title);
			fprintf(output, "Genre: %s\n", temporary->genre);
			fprintf(output, "Year: %d\n", temporary->year);
			fprintf(output, "Album/Singl: %s\n", temporary->albsin);
			fprintf(output, "-----------------\n");
			temporary = temporary->next;
		}
	}
	fclose(output);
}

void read_from_file() {
	FILE* input;
	fopen_s(&input, "input.txt", "r");
	node* newelem_file = (node*)malloc(sizeof(node));

	newelem_file->genre = get_string_from_file(input);
	newelem_file->singer_title = get_string_from_file(input);
	newelem_file->song_title = get_string_from_file(input);

	char* string = get_string_from_file(input);
	if (strcmp(string,"Singl"))
	{
		newelem_file->albsin.singl = string;
	}
	else
	{
		newelem_file->albsin.album = string;
	}
	
	int year;
	fscanf_s(input, "%d", &year);
	newelem_file->year = year;

	newelem_file->next = head;
	head = newelem_file;

	fclose(input);
	printf("Addition is completed\n");
}

enum choice
{
	print = 1,
	add = 2,
	remove1 = 3,
	write = 4,
	read = 5,
	find = 6,
	exit1 = 7,
};

int main() {
	int choice;
	bool flag = true;
	while (flag)
	{
		printf("\nChoose the action:\n 1 - print full base\n 2 - add element\n 3 - remove element\n 4 - write to file\n 5 - read from file\n 6 - find element\n 7 - exit\nYour choice:");
		scanf_s("%d", &choice);
		printf("\n");
		switch (choice)
		{
		case print:
			printf("print full base\n");
			print_base();
			break;
		case add:
			printf("add element\n");
			getchar();
			add_element();
			break;
		case remove1:
			printf("remove element\n");
			delete_element();;
			break;
		case write:
			printf("write to file\n");
			write_to_file();
			break;
		case read:
			printf("read from file\n");
			read_from_file();
			break;
		case find:
			printf("find element\n");
			find_element();
			break;
		case exit1:
			printf("exit");
			flag = false;
			break;
		default:
			printf("Incorrect input, please try again\n");
			break;
		}
	}
}