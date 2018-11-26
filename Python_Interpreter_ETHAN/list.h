#pragma once
#include <stdbool.h>

typedef struct Node {
	char *value;
	struct Node* next;
} Node;

typedef struct List {
	Node* head;
	Node* last;
	int length;
} List;

Node* new_node(char*);
List* new_list(void);
void add_value(List*, char*);
bool is_empty(List*);
void add_first(List*, char*);
void print_list(List*);
void reverse_list(List*);
List* new_list_space(char*);
void fill_list(List*, char*);
void print_given_lst_Vlist(List*);
List* new_list_parenthese(char*);
List* new_list_equals(char*);








