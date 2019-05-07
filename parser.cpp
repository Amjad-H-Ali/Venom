#include <iostream>
#include "parser.h"

namespace utils = parser::utility;


void parser::parser(token::Token *current, token::Token *previous) {

	// Exit code for recursive Function. (End of Linked List)
	if(!current) return;

	// Next Token in Linked List.
	token::Token *next = current->getNext();

	parser(next, current);

};


bool utils::validStartToList(token::Symbol tokenType) {

	return tokenType == token::BAR;
};




