#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <stdbool.h>

struct level {
	long double data;
	struct level *next;
};

struct level *top = NULL;

void push(long double input) {
	struct level *nptr = malloc(sizeof(struct level));
	nptr->data = input;
	nptr->next = top;
	top = nptr;
}

void pop() {
	if (top == NULL)
		printf("Empty\n");
	else {
		struct level *temp;
		temp = top;
		top = top->next;
		free(temp);
	}
}

void display() {
	printf("\n[Stack]\n");
	if (top == NULL) {
		printf("Empty\n");
		return;
	} else {
		struct level *temp;
		temp = top;
		while (temp != NULL) {
			printf("%Lf\n", temp->data);
			temp = temp->next;
		}
	}
	printf("\n");
}

bool checkNumeric(char* input) {
	for (size_t i = 0; i <= strlen(input) - 2; i++) {
		if (!isdigit(input[i]))

			return false;
	}
	return true;
}

void quit(int sig) {
	if (sig == SIGINT) {
		printf("\n");
		while (top != NULL)
			pop();
		display();
		exit(0);
	}
}

void add() {
	struct level *temp;
	temp = top;
	long double a = temp->data;
	pop();

	temp = temp->next;
	long double b = temp->data;
	pop();

	b += a;
	
	push(b);
}

void sub() {
	struct level *temp;
	temp = top;
	long double a = temp->data;
	pop();

	temp = temp->next;
	long double b = temp->data;
	pop();

	b -= a;
	
	push(b);
}

void divide() {
	struct level *temp;
	temp = top;
	long double a = temp->data;
	pop();

	temp = temp->next;
	long double b = temp->data;
	pop();

	b /= a;
	
	push(b);
}

void mult() {
	struct level *temp;
	temp = top;
	long double a = temp->data;
	pop();

	temp = temp->next;
	long double b = temp->data;
	pop();

	b *= a;
	
	push(b);
}

void main() {
	display();
	signal(SIGINT, quit);

	for (;;) {
		int i = 0;
		char *buffer;
		size_t bufferSize = 32;

		buffer = (char *)malloc(bufferSize * sizeof(char));
		if (buffer == NULL) {
			perror("Buffer allocate error\n");
			exit(1);
		}

		size_t input = getline(&buffer, &bufferSize, stdin);

		if (checkNumeric(buffer))
			push(atof(buffer));
		else if (strcmp(buffer, "+\n") == 0)
			add();
		else if (strcmp(buffer, "-\n") == 0)
			sub();
		else if (strcmp(buffer, "/\n") == 0)
			divide();
		else if (strcmp(buffer, "*\n") == 0)
			mult();
		else
			printf("Invalid op\n", buffer);

		display();
	}
}