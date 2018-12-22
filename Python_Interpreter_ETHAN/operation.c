#include "list.h"
#include "operation.h"
#include "variable.h"
#include <stdio.h>
#include <string.h>

Operation* str2operation(char* str)
{
	Operation *op = (Operation*)malloc(sizeof(Operation));
	List *lst_plus = new_list_plus(str);
	List *lst_minus = new_list_minus(str);
	List *lst_kaful = new_list_kaful(str);
	List *lst_div = new_list_div(str);
	if (lst_plus->length > 0)
	{
		op->optr = malloc(2);
		strncpy(op->optr,"+",1);
		op->operands = lst_plus;
	}
	else if (lst_minus->length > 0)
	{
		op->optr = malloc(2);
		strncpy(op->optr, "-", 1);
		op->operands = lst_minus;
	}
	else if (lst_kaful->length > 0)
	{
		op->optr = malloc(2);
		strncpy(op->optr, "*", 1);
		op->operands = lst_kaful;
	}
	else if (lst_div->length > 0)
	{
		op->optr = malloc(2);
		strncpy(op->optr, "/", 1);
		op->operands = lst_div;
	}
	else
	{
		List *lst = new_list();
		add_value(lst,str);
		op->operands = lst;
	}
}

char *op_result(ListVar* lstvar, Operation* op)
{
	char *res = (char*)malloc(sizeof(char));
	strcpy(res, "");
	int type_str = kind_of_string(lst_plus->head->value);

	if (strncmp(op->optr, "+", 1))
	{

	}
}


int kind_of_string(char *recv) {
	int n = strlen(recv) - 1;
	if (recv[0] == '\''&& recv[n] == '\'')
		return 1;
	else if (recv[0] == '\"'&& recv[n] == '\"')
		return 2;
	return 0;
}