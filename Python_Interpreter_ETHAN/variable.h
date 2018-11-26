#pragma once

typedef struct Variable {
	char *type;
	int value_int;
	char *value_string;
	char *name;
	struct Variable* next;
} Variable;

typedef struct ListVar {
	Variable* head;
	Variable* last;
	int length;
} ListVar;

Variable* new_var(char*, char*, char*);





