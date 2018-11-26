#include <stdio.h>
#include "ui_utils.h"
#include "parser.h"
#include "variable.h"

int main() {
	printf("Mython - My Python Interpreter version 1.0 by [ETHAN BARKATE]\n");
	char *input = (char*)malloc(sizeof(char*));
	ListVar *lstvar = new_list_var();
	while (1)
	{
		printf("\n>>> ");
		read_line(input, 300, stdin);
		parseString(lstvar,input);
	}

	return 0;

}