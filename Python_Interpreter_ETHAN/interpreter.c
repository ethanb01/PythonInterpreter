#include <stdio.h>
#include "ui_utils.h"
#include "parser.h"

int main() {
	printf("Mython - My Python Interpreter version 1.0 by [ETHAN BARKATE]\n");
	char *input = (char*)malloc(sizeof(char*));
	while (1)
	{
		printf("\n>>> ");
		read_line(input, 300, stdin);
		parseString(input);
	}

	return 0;

}