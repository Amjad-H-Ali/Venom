#pragma once
#include "Token.h"
#include "Identifier.h"

using namespace std;

struct Tokens {
	Token *token_head;
	Tokens *next;
};

char *get_string(char &c, ifstream &in);
char *get_identifier(char &c, ifstream &in);
char *get_operator(char &c, ifstream &in);
Token *get_array_values(char *c, ifstream &in);
Type which_identifier(char *identifier_ptr, char &c, ifstream &in);
Type which_operator(char *c);
int length_of_type(char &c, ifstream &in, bool(*green_light)(const char));
bool names_match(char *s1, char *s2);
bool is_operator(char &c, ifstream &in);
bool is_AtoZ(const char &c);
bool not_quotes(const char &c);
