#include <iostream>
#include "parser.h"
// #include "Declarations.h"

void parser(token::Token *current, token::Token *previous) {

	// Exit code for recursive Function. (End of Linked List)
	if(!current) return;

	// Next Token in Linked List.
	token::Token *next = current->getNext();

	parser(next, current);


	
};