#include <iostream>
#include "parser.h"

namespace utils = parser::utility;


void parser::parser(token::Token *current, token::Token *previous) {

	// Exit code for recursive Function. (End of Linked List)
	if(!current) return;

	// Next Token in Linked List.
	token::Token *next = current->getNext();

	parser(next, current);

	std::cout << utils::validStartToList(current) << std::endl;

};



// Utility Functions to help parse Tokens

bool utils::validStartToList(token::Token *tokenPtr) {

	token::Symbol tokenType = tokenPtr->getType();

	return tokenType == token::BAR;
};




