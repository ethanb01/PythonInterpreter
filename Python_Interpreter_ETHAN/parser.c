#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "list.h"
#include "variable.h"
#include "operation.h"

void print_func(ListVar*, char*);
void create_variable(ListVar*, char*, char*);
void quit_func(char*);
int kind_of_string(char*);
char* str_without_two(char*);
char* str_without_one(char*);
char* return_var_value(char*,ListVar*);
void free_all(List*, List*, List*, List*);
int want_variable=0;

void parseString(ListVar* lstvar, char* input) {
	want_variable = 0;
	quit_func(input);//check if the user want to quit
	want_new_variable(lstvar, input);
	print_func(lstvar,input);
}


void quit_func(char* input) {
	if (strcmp(input, "exit()") == 0 || strcmp(input, "quit()") == 0)
		exit(1);
	else if (strcmp(input, "exit") == 0) {
		want_variable = 1;
		printf("You need to write exit() to exit");
	}
	
}


void print_func(ListVar* lstvar, char *input) {
	List *lst = new_list_parenthese(input);
	char *to_print = return_var_value(lst->last->value,lstvar);
	if ((strcmp(lst->head->value, "print") == 0)||(strcmp(lst->head->value, "print ") == 0))
	{
		to_print = str_without_two(to_print);
		printf("%s", to_print);
	}
	else
	{
		if (want_variable != 1)
			printf("WHAT DO YOU WANT???");
	}

}


//function that receive a string a return 1 if the string is between '' or return 2 if between "" or 0 is not between
int kind_of_string(char *recv) {
	int n = strlen(recv) - 1;
	if (recv[0] == '\''&& recv[n] == '\'')
		return 1;
	else if (recv[0] == '\"'&& recv[n] == '\"')
		return 2;
	return 0;
}
//function that receive a string between two "" and return the string without the 2 ""
char* str_without_two(char *recv) {
	char *to_return = strtok(recv, "\"");
	return to_return;
	
}
//function that receive a string between two '' and return the string without the 2 ''
char* str_without_one(char *recv) {
	char *to_return = strtok(recv, "\'");
	return to_return;

}


//function that receive input and call to the function create_variable if wanted to create a variable OR return 0
int want_new_variable(ListVar* lstvar, char *input) {
	List *lst = new_list_equals(input);
	char *name = lst->head->value;
	char *value = lst->last->value;

	
  	if (lst->length == 2) 
	{
		want_variable = 1;
		create_variable(lstvar, name, value);
		return 1;
	}
	else
	{
		want_variable = 0;
		return 0;
	}
	
}

//function that create a variable
void create_variable(ListVar* lstvar, char* name, char *value) {
	char *type=NULL;//int or string
	char *var_value = return_var_value(value,lstvar);//the value to be put in the variable
	int is_number = is_num(var_value);//if the variable is an integer ==1
	int is_string = kind_of_string(var_value);//check if it is a string ==1

	if ((is_string == 1) || (is_string == 2)) {//check if it is a string 
		type = "string";
		//if (is_string == 1) //''
		//	strcpy(var_value, str_without_one(var_value));
		//else if (is_string == 2)//""
		strcpy(var_value, str_without_two(var_value));
		add_value_var(lstvar, name, var_value, type);//add the string variable to the list of variables
	}
	else if (is_number == 1) { // IS INTEGER
		type = "integer";
		add_value_var(lstvar, name, var_value, type);
	}
	else 
	{
		printf("SyntaxError invalaid value");
	}
}

//function that receive all the string after the '=' and parse it and return the value (in char)
char* return_var_value(char* value, ListVar *lstvar) { // todo eli: rhs value
	char *res = (char*)malloc(sizeof(char));
	strcpy(res, "");
	
	int first = 0, second = 0,result;
	Operation* op = str2operation(value);
	
	List *lst_plus = new_list_plus(value);
	List *lst_minus = new_list_minus(value);
	List *lst_kaful = new_list_kaful(value); 
	List *lst_div = new_list_div(value);
	int type_str = kind_of_string(lst_plus->head->value);

	if (lst_plus->length == 2) { //List PLUS
		//////// first
		if (type_str == 1) 
		{
			strcat(res,"\"");
			strcat(res,str_without_one(lst_plus->head->value));
		}
		else if (type_str == 2)
		{
			strcat(res, "\"");
			strcat(res, str_without_two(lst_plus->head->value));
		}
		else if (is_num(lst_plus->head->value))
		{
			first = atoi(lst_plus->head->value);
		}
		else if (get_var_by_name(lstvar, lst_plus->head->value) != NULL) {
			Variable *varf = get_var_by_name(lstvar, lst_plus->head->value);
			if (strcmp(varf->type, "string") == 0)
			{
				strcat(res, "\"");
				strcat(res, varf->value_string);
			}
			else if (strcmp(varf->type, "integer") == 0)
			{
				first = varf->value_int;
			}
		}

		////// SECOND
		if (type_str == 1) {
			strcat(res, str_without_one(lst_plus->last->value));
			strcat(res, "\"");
		}
		else if (type_str == 2)
		{
			strcat(res, str_without_two(lst_plus->last->value));
			strcat(res, "\"");
		}
		else if (get_var_by_name(lstvar, lst_plus->last->value) != NULL) {
			Variable *varf = get_var_by_name(lstvar, lst_plus->last->value);
			if (strcmp(varf->type, "string") == 0)
			{
				strcat(res, varf->value_string);
				strcat(res, "\"");
			}
			else if (strcmp(varf->type, "integer") == 0)
			{
				second = varf->value_int;
				result = first + second;
				itoa(result, res, 10);
			}
		}
		else if (is_num(lst_plus->last->value)) 
		{
			second = atoi(lst_plus->last->value);
			result = first + second;
			itoa(result, res, 10);
		}
	}
	else if (lst_minus->length == 2) { ///////////////List MINUS
		//////// first
		if (type_str == 1)
		{
			strcpy(res, "Impossible to do substraction to strings");
		}
		else if (type_str == 2)
		{
			strcpy(res, "Impossible to do substraction to strings");
		}
		else if (is_num(lst_kaful->head->value))
		{
			first = atoi(lst_minus->head->value);
		}
		else if (get_var_by_name(lstvar, lst_minus->head->value) != NULL) {
			Variable *varf = get_var_by_name(lstvar, lst_minus->head->value);
			if (strcmp(varf->type, "string") == 0)
			{
				strcpy(res, "Impossible to do substraction to strings");
			}
			else if (strcmp(varf->type, "integer") == 0)
			{
				first = varf->value_int;
			}
		}

		////// SECOND
		if (type_str == 1) {
			strcpy(res, "Impossible to do substraction to strings");
		}
		else if (type_str == 2)
		{
			strcpy(res, "Impossible to do substraction to strings");
		}
		else if (get_var_by_name(lstvar, lst_minus->last->value) != NULL) {
			Variable *varf = get_var_by_name(lstvar, lst_minus->last->value);
			if (strcmp(varf->type, "string") == 0)
			{
				strcpy(res, "Impossible to do substraction to strings");

			}
			else if (strcmp(varf->type, "integer") == 0)
			{
				second = varf->value_int;
				result = first + second;
				itoa(result, res, 10);
			}
		}
		else if (is_num(lst_minus->last->value))
		{
			second = atoi(lst_plus->last->value);
			result = first + second;
			itoa(result, res, 10);
		}
	}
	else if (lst_kaful->length == 2) { ///////////////List KAFUL
		//////// first
		if (type_str == 1)
		{
			strcpy(res, "Impossible to do multiplication to strings");
		}
		else if (type_str == 2)
		{
			strcpy(res, "Impossible to do multiplication to strings");
		}
		else if (is_num(lst_kaful->head->value))
		{
			first = atoi(lst_kaful->head->value);
		}
		else if (get_var_by_name(lstvar, lst_kaful->head->value) != NULL) {
			Variable *varf = get_var_by_name(lstvar, lst_kaful->head->value);
			if (strcmp(varf->type, "string") == 0)
			{
				strcpy(res, "Impossible to do multiplication to strings");
			}
			else if (strcmp(varf->type, "integer") == 0)
			{
				first = varf->value_int;
			}
		}

		////// SECOND
		if (type_str == 1) {
			strcpy(res, "Impossible to do multiplication to strings");
		}
		else if (type_str == 2)
		{
			strcpy(res, "Impossible to do multiplication to strings");
		}
		else if (get_var_by_name(lstvar, lst_kaful->last->value) != NULL) {
			Variable *varf = get_var_by_name(lstvar, lst_kaful->last->value);
			if (strcmp(varf->type, "string") == 0)
			{
				strcpy(res, "Impossible to do multiplication to strings");

			}
			else if (strcmp(varf->type, "integer") == 0)
			{
				second = varf->value_int;
				result = first + second;
				itoa(result, res, 10);
			}
		}
		else if (is_num(lst_kaful->last->value))
		{
			second = atoi(lst_plus->last->value);
			result = first + second;
			itoa(result, res, 10);
		}
	}
	else if (lst_div->length == 2) { ///////////////List KAFUL
		//////// first
		if (type_str == 1)
		{
			strcpy(res, "Impossible to do division to strings");
		}
		else if (type_str == 2)
		{
			strcpy(res, "Impossible to do division to strings");
		}
		else if (is_num(lst_div->head->value))
		{
			first = atoi(lst_div->head->value);
		}
		else if (get_var_by_name(lstvar, lst_div->head->value) != NULL) {
			Variable *varf = get_var_by_name(lstvar, lst_div->head->value);
			if (strcmp(varf->type, "string") == 0)
			{
				strcpy(res, "Impossible to do division to strings");
			}
			else if (strcmp(varf->type, "integer") == 0)
			{
				first = varf->value_int;
			}
		}

		////// SECOND
		if (type_str == 1) {
			strcpy(res, "Impossible to do division to strings");
		}
		else if (type_str == 2)
		{
			strcpy(res, "Impossible to do division to strings");
		}
		else if (get_var_by_name(lstvar, lst_div->last->value) != NULL) {
			Variable *varf = get_var_by_name(lstvar, lst_div->last->value);
			if (strcmp(varf->type, "string") == 0)
			{
				strcpy(res, "Impossible to do division to strings");

			}
			else if (strcmp(varf->type, "integer") == 0)
			{
				second = varf->value_int;
				result = first + second;
				itoa(result, res, 10);
			}
		}
		else if (is_num(lst_div->last->value))
		{
			second = atoi(lst_plus->last->value);
			result = first + second;
			itoa(result, res, 10);
		}
	}
	else
	{
		Variable *varf = get_var_by_name(lstvar, value);
		if (varf != NULL)
		{
			if (varf->value_int != NULL)
				itoa(varf->value_int, res, 10);
			else if (varf->value_string !=NULL)
				strcpy(res, varf->value_string);
		}
		else if ((kind_of_string(value) == 0) && (is_num(value) == 0))
			strcpy(res, "SytaxError you need choukchick OR Variable dont exist");
		else
			strcpy(res, value);
	}
	free_all(lst_plus, lst_minus, lst_kaful, lst_div);
	return res;

}
//function that receive a string value and return 1 if it is a digit else return 0
int is_num(char *value) {
	if (isdigit(value[0]) != 0) { // IS INTEGER
		int num = 1;
		for (int i = 1; i < strlen(value); i++)
		{
			if (isdigit(value[i]) == 0)
				num = 0;
		}
		return num;
	}
}

void free_all(List *lst1, List *lst2, List *lst3, List *lst4) {
	free(lst1);
	free(lst2);
	free(lst3);
	free(lst4);
}