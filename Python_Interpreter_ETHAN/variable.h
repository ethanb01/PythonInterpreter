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
ListVar* new_list_var(void);
void add_value_var(ListVar*, char*, char*, char*);
Variable* get_var_by_name(ListVar*, char*);





