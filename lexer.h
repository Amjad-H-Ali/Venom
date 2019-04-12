#pragma once
#include "Token.h"
#include "Identifier.h"

using namespace std;

struct Tokens {
	Token *token_head;
	Tokens *next;
};
void lexer(char *file_name);
void get_string(string &s, ifstream &in);
bool strings_match(string &s1, char *s2);
Type which_identifier(string &s);
Type which_operator(string &s);