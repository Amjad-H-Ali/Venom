#pragma once
#include "Token.h"

struct Defined {
	Token *token_address;
	Defined *paths[26];

	// Initialize all pointers in array to NULL.
	Defined():paths(){};
};

void define(Token *token_ptr);

Token *is_defined(char *name);

int hash(char letter);