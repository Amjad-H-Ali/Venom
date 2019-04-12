#pragma once
#include "Token.h"
#include "Identifier.h"
// #include "STRING.h"
// #include "VAR.h"
// #include "OPERATOR.h"


struct Stmnt {
	Token *value;
	Stmnt *next;
};

void lexer(char *file_name);