#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "variable.h"

bool is_lstvar_empty(ListVar*);
void remove_first(ListVar*);
void remove_last(ListVar*);
void remove_by_var(ListVar*, Variable*);
Variable* get_var_by_name(ListVar*, char*);
void remove_by_name(ListVar*, char*);

Variable* new_var(char *name, char *value, char *type) {
	Variable* var = (Variable*)malloc(sizeof(Variable));

	var->name = malloc(strlen(name) + 1);
	var->type = malloc(strlen(type) + 1);
	strcpy(var->name, name);
	strcpy(var->type, type);
	if (strcmp(type, "string") == 0) {
		var->value_string = malloc(strlen(value) + 1);
		strcpy(var->value_string, value);
		var->value_int = NULL;
	}
	else if(strcmp(type, "integer") == 0)
	{
		var->value_int = atoi(value);
		var->value_string = NULL;
	}
	var->next = NULL;
	return var;

}

ListVar* new_list_var(void) {
	ListVar *lstvar = (ListVar*)malloc(sizeof(ListVar));
	lstvar->head = NULL;
	lstvar->last = NULL;
	lstvar->length = 0;
	return lstvar;
}

void add_value_var(ListVar* self, char *name, char *value, char *type) {
	if (get_var_by_name(self, name)!=NULL) {
		remove_by_name(self, name);
	}


	Variable *to_add = new_var(name, value, type);
	if (is_lstvar_empty(self)) {
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

bool is_lstvar_empty(ListVar* self) {
	return (self->length == 0);
}



Variable* get_var_by_name(ListVar *self, char *name)
{
	Variable *curr = self->head;
	while (curr != NULL)
	{
		if (strcmp(curr->name, name) == 0)
			return curr;
		curr = curr->next;
	}
	return NULL;
}

void remove_by_name(ListVar *self,char *name)
{
	if (strcmp(self->head->name,name)==0) // case its the first var
		remove_first(self);
	else if (strcmp(self->last->name, name) == 0) // case its the last var
		remove_last(self);
	else // case its not end or start
	{
		Variable *toRemove = get_var_by_name(self, name);
		remove_by_var(self,toRemove);
		self->length--;
	}
}

void remove_first(ListVar *self) {
	if (self->head == NULL)
		self->length = 0;
	else
	{
		self->head = self->head->next;
		self->length--;
	}
}

void remove_last(ListVar *self) {
	if (self->head == NULL) {
		self->length = 0;
	}
	else if (self->length == 1) {
		self->head = NULL;
		self->length = 0;
	}
	else {
		Variable *curr = self->head;
		for (int i = 1; i <= self->length -2; i++)
			curr = curr->next;
		curr->next = NULL;
		self->length--;
	}
}

void remove_by_var(ListVar* self, Variable* toRemove)
{
	/* if the node is in the middle */
	Variable* curr = self->head;
	while (curr != NULL)
	{
		if (curr->next = toRemove)
			break;
		curr = curr->next;
	}
	curr->next = curr->next->next;

}
