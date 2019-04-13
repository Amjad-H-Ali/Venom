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


// int array[10] = {1, 2, 3, 4, 5}

// array |1, 2, 3, 4, 5, 6, 7|


// int array[][10] = {{},{}, {}, {}, {}}

// array |1, 2, 3, 4, 5, 6, 7|

