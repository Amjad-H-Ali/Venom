#pragma once
#include <iostream>
#include <string.h>
#include <fstream>
#include "Token.h"
#include "STRING.h"
#include "VAR.h"
#include "OPERATOR.h"

using namespace std;

struct Stmnt {
	Token *value;
	Stmnt *next;
};

void lexer(char *file_name);