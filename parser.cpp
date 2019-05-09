#include <iostream>
#include "parser.h"
#include <utility>

namespace utils = parser::utility;


void parser::parser(token::Token *current) {

	// Exit code for recursive Function. (End of Linked List)
	if(!current) return;

	// Pointer to new AST node
	AST *newAST = nullptr;

	// Next Token in Linked List.
	token::Token *next = current->getNext();
	// Previous Token in Linked List.
	token::Token *prev = current->getPrev();

	parser(next);

	// Instantiate AST_ID object and return to
	// previous Token in list.
	if(*current == token::IDENTIFIER) {
		std::cout << "Yes" << std::endl;

		// Calls R-Value Constructor to steal Dynamically allocated 
		// data from Token Object since we will no longer need Token.
		newAST = new class AST_ID(AST_ID, std::move(*current));
		// return newAST;
	}

	// Instantiate AST_BinaryOp object and set values
	// to left and right AST Nodes.
	// if(current->getType() == IS)

};



// AST_List *parser::parseList()

// Utility Functions to help parse Tokens

bool utils::validStartToList(token::Token *tokenPtr) {

	token::Symbol tokenType = tokenPtr->getType();

	return tokenType == token::BAR;
};






