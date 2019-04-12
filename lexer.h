#pragma once
#include "Token.h"
#include "Identifier.h"

// #include "STRING.h"
// #include "VAR.h"
// #include "OPERATOR.h"


struct Tokens {
	Token *token_node;
	Tokens *next;
};

void parse_string(string &s, ifstream &in);
bool strings_match(string &s1, char *s2);
Type which_identifier(string &s);
Type which_operator(string &s);