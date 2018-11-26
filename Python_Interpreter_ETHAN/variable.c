#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "variable.h"

Variable* new_var(char *name, char *value, char *type) {
	Variable* var = (Variable*)malloc(sizeof(Variable));

	//var->name = malloc(strlen(str) + 1);
	strcpy(var->name, name);
	strcpy(var->type, type);
	if (strcmp(type, "string") == 0) {
		strcpy(var->value_string, value);
		var->value_int = NULL;
	}
	else if(strcmp(type, "integer") == 0)
	{
		strcpy(var->value_int,(int)value);
		var->value_string = NULL;
	}
	var->next = NULL;
	return var;
}
