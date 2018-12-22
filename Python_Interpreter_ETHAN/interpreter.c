#include <stdio.h>
#include "ui_utils.h"
#include "parser.h"
#include "variable.h"

int main(int argc, char** argv) {
	printf("Mython - My Python Interpreter version 1.0 by [ETHAN BARKATE]\n");
	char input[128]="";
	ListVar *lstvar = new_list_var(); // to hashmap
	while (1)
	{
		printf("\n>>> ");
		read_line(input, 300, stdin); 
		parseString(lstvar,input);
		// add eval 
	}
	
	return 0;

}