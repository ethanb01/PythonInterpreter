#include <stdio.h>
#include <stdlib.h>
#include "list.h"


bool is_empty(List*);


Node* new_node(char *str) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = malloc(strlen(str)+1);
	strcpy(node->value, str);
	node->next = NULL;
	return node;
}


// create list: gets void and returns new list
List* new_list(void) {
	List *lst = (List*)malloc(sizeof(List));
	lst->head = NULL;
	lst->last = NULL;
	lst->length = 0;
	return lst;
}
// create list from input : gets char* and returns new list
List* new_list_space(char *input) {
	List *lst = (List*)malloc(sizeof(List));
	lst->head = NULL;
	lst->last = NULL;
	lst->length = 0;

	char copy_input[1024];
	strcpy(copy_input, input);
	int i = 0;
	char *p = strtok(copy_input, " ");
	//add_value(lst, p);
	while (p != NULL)
	{
		add_value(lst, p);
		p = strtok(NULL, " ");
	}

	return lst;
}


// create list from input : gets char* and returns new list
List* new_list_parenthese(char *input) {
	List *lst = (List*)malloc(sizeof(List));
	lst->head = NULL;
	lst->last = NULL;
	lst->length = 0;

	char copy_input[1024];
	strcpy(copy_input, input);
	int i = 0;
	const char* del = "()";
	char *p = strtok(copy_input,del);
	/*if (p != "print" || p != "print ") {
		add_value(lst,p);
		return lst;
	}*/
	//char copy_p[1024];
	while (p != NULL)
	{
		//strcpy(copy_p, p);
		add_value(lst, p);
		p = strtok(NULL,del);
	}

	return lst;
}



// create list from input : gets char* and returns new list
List* new_list_equals(char *input) {
	List *lst = (List*)malloc(sizeof(List));
	lst->head = NULL;
	lst->last = NULL;
	lst->length = 0;

	char copy_input[1024];
	strcpy(copy_input, input);
	int i = 0;
	const char *del = "=";
	char *p = strtok(copy_input, del);

	//add_value(lst, p);
	while (p != NULL)
	{
		add_value(lst, p);
		p = strtok(NULL, "");
	}

	return lst;
}
void fill_list(List* self, char *input) {
	self->head = NULL;
	self->last = NULL;
	self->length = 0;

	char copy_input[30];
	strcpy(copy_input, input);
	int i = 0;
	char *p = strtok(copy_input, " ");
	//add_value(lst, p);
	while (p != NULL)
	{
		add_value(self, p);
		p = strtok(NULL, " ");
	}

}



void print_given_lst_Vlist(List* self) {
	printf(self->head->value);
}


// function gets int and add Node to the list
void add_value(List* self, char *str) {
	Node* to_add = new_node(str);


	if (is_empty(self)) {
		self->head = to_add;
		self->last = to_add;
	}
	else
	{
		self->last->next = to_add;
		self->last = to_add;
	}
	self->length++;
}

bool is_empty(List* self) {
	return (self->length == 0);
}

void add_first(List* self, char *str) {
	Node* first_to_add = new_node(str);

	first_to_add->next = self->head;
	self->head = first_to_add;
}


void reverse_list(List* self)
{
	Node* prev = NULL;
	Node* current = self->head;
	Node* next = NULL;
	while (current != NULL)
	{
		next = current->next;

		current->next = prev;

		prev = current;
		current = next;
	}
	self->head = prev;
}

void print_list(List* self) {
	Node* current = self->head;
	if (current != NULL)
		printf("[");

	while (current != NULL) {
		if (current->next == NULL) {
			printf("%s]\n", current->value);
			current = current->next;
		}
		else
		{
			printf("%s, ", current->value);
			current = current->next;
		}
	}
}

