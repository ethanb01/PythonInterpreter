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


void parseString(char* input) {
	check_quit(input);//check if the user want to quit
	is_first_print(input);
	want_new_variable(input);
	check_print_func(input);
	
	
	
}

void check_quit(char* input) {
	if (strcmp(input, "exit()") == 0 || strcmp(input, "quit()") == 0)
		exit();
}


int check_print_func(char *input) {
	List *lst = new_list_parenthese(input);
	if ((strcmp(lst->head->value, "print") == 0)||(strcmp(lst->head->value, "print ") == 0)) {
#pragma region old Print
		/*Node *current = lst->head->next;
Node *lastword = lst->last;
int l = lst->length - 1;
int w = strlen(lastword->value) - 1;
int is_first = 1;
int i;
if (current != NULL)
{
	if ((current->value[0] == '\'' && lastword->value[w] == '\'')
		|| (current->value[0] == '\"' && lastword->value[w] == '\"')) {
		while (current != NULL) {
			if (is_first == 1) {
				for (i = 1; i < strlen(current->value) - 1; i++)
				{
					printf("%c", current->value[i]);
				}
				is_first = 0;
			}
			else
			{
				for (i = 0; i < strlen(current->value) - 1; i++)
				{
					if (i == 0)
						printf(" %c", current->value[i]);
					else
						printf("%c", current->value[i]);
				}
			}
			current = current->next;
		}
	}
}
*/
#pragma endregion
		if (is_string_correct(lst->last->value) == 1) {
			printf("%s", return_str_without_one(lst->last->value));
		}
		else if(is_string_correct(lst->last->value) == 2)
			printf("%s", return_str_without_two(lst->last->value));
		else if (is_variable(lst->last->value))
		{
			//print variable value
		}
		else
			printf("SytaxError you need choukchick");
		
		
	}
	else
		is_variable(input);

	return 1;
}

int is_variable(char *input) {
		
	return 0;
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

int want_new_variable(char *input) {
	List *lst = new_list_equals(input); 
	char name[1024]; char value[1024];
	strcpy(name, lst->head->value);
	strcpy(value, lst->last->value);
	
	if (lst->length == 2) {
		create_variable(name,value);
	}
}

int create_variable(char* name, char *value) {
	char *type;
	char test = '5';
	if ((is_string_correct(value) == 1) || (is_string_correct(value) == 2)) {
		type = "string";
		Variable *v = new_var(name, value, type);
	}
	else if (isdigit(value[0])!=0) {
		for (int i = 1; i < strlen(value)-1; i++)
		{
			if (isdigit(value[i]) != 0)
				type = "integer";
		}
		type = "integer";
		Variable *v = new_var(name, value, type);
	}
	else
		printf("SyntaxError invalaid value");
	
}


int is_first_print(char *input) {
	const char copy_input[1024];
	strcpy(copy_input, input);
	char first[30];
	strcpy(first, "");
	if (strlen(copy_input) < 7)
		return 0;//not enof to print
	for (int i = 0; i < 5; i++)
	{
		strcpy(first[i],copy_input[i]);
	}
}



