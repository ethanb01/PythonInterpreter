#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "list.h"
#include "variable.h"

void check_quit(char*);
int check_print_func(List*);
int is_string_correct(char*);
char* return_str_without_two(char*);
char* return_str_without_one(char*);
Variable* is_variable(ListVar*, char*);


int want_variable = 0;

void parseString(ListVar* lstvar, char* input) {
	want_variable = 0;
	check_quit(input);//check if the user want to quit
	want_new_variable(lstvar, input);
	check_print_func(lstvar,input);
	
	
	
}

void check_quit(char* input) {
	if (strcmp(input, "exit()") == 0 || strcmp(input, "quit()") == 0)
		exit();
}


int check_print_func(ListVar* lstvar, char *input) {
	List *lst = new_list_parenthese(input);
	Variable *maybe = is_variable(lstvar, lst->last->value);
	if ((strcmp(lst->head->value, "print") == 0)||(strcmp(lst->head->value, "print ") == 0)) {

		if (is_string_correct(lst->last->value) == 1) {
			printf("%s", return_str_without_one(lst->last->value));
		}
		else if(is_string_correct(lst->last->value) == 2)
			printf("%s", return_str_without_two(lst->last->value));
		else if (maybe!=NULL)
		{
			if (strcmp(maybe->type,"integer")==0)
				printf("%d", maybe->value_int);
			else
				printf("%s", maybe->value_string);
		}
		else
			printf("SytaxError you need choukchick");
		
		
	}
	else
	{
		if (want_variable != 1)
			printf("WHAT DO YOU WANT???");
	}

	return 1;
}

Variable* is_variable(ListVar* lstvar, char *name) {
	Variable *toReturn = get_var_by_name(lstvar, name);
	if (toReturn != NULL)
		return toReturn;
	else
		return NULL;
}

int is_string_correct(char *recv) {
	int n = strlen(recv) - 1;
	if (recv[0] == '\''&& recv[n] == '\'')
		return 1;
	else if (recv[0] == '\"'&& recv[n] == '\"')
		return 2;
	return 0;
}
char* return_str_without_two(char *recv) {
	char *to_return = strtok(recv, "\"");
	return to_return;
	
}
char* return_str_without_one(char *recv) {
	char *to_return = strtok(recv, "\'");
	return to_return;

}

int want_new_variable(ListVar* lstvar, char *input) {
	List *lst = new_list_equals(input);
	char *name= NULL; char *value= NULL;
	name = lst->head->value;
	value = lst->last->value;
	
  	if (lst->length == 2) {
		want_variable = 1;
		create_variable(lstvar, name, value);
	}
	
	return 0;
}

int create_variable(ListVar* lstvar, char* name, char *value) {
	char *type=NULL;
	if ((is_string_correct(value) == 1) || (is_string_correct(value) == 2)) {
		type = "string";
		if (is_string_correct(value) == 1) {
			strcpy(value, return_str_without_one(value));
		}
		else if (is_string_correct(value) == 2) 
			strcpy(value, return_str_without_two(value));
		add_value_var(lstvar,name, value, type);
	}
	else if (isdigit(value[0])!=0) {
		int isNum = 1;
		for (int i = 1; i < strlen(value); i++)
		{
			if (isdigit(value[i]) == 0)
				isNum = 0;
		}
		if (isNum == 1) {
			type = "integer";
			add_value_var(lstvar, name, value, type);
		}
	}
	else
		printf("SyntaxError invalaid value");
	
}



