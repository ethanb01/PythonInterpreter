#pragma once
#include "list.h"

typedef struct Operation {
	char *optr; // +,-,*,/,^, =, ...
	List* operands;
} Operation;

Operation* str2operation(char*);

