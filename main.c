#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

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

int checkNumeric(char* input) {

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
		char input[32];
		for (; (input[i] = getchar()) && input[i] != '\n'; i++){}

		if (atof(input) != 0)
			push(atof(input));
		else if (strcmp(input, "+\n") == 0)
			add();
		else if (strcmp(input, "-\n") == 0)
			sub();
		else if (strcmp(input, "/\n") == 0)
			divide();
		else if (strcmp(input, "*\n") == 0)
			mult();
		else
			printf("<%s>", input);

		display();
	}
}