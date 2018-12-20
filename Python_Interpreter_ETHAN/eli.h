#pragma once
#include "list.h"

typedef struct Operation {
	char optr; // +,-,*,/,^, =, ...
	List* operands;
} operation;

