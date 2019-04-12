#pragma once
#include "Token.h"

struct Declared {
	Token *token_address;
	Declared *paths[26];

	// Initialize all pointers in array to NULL.
	Declared():paths(){};
};



void declare(Token *token_ptr);

Token *is_declared(char *name);

int hash(char letter);



