#include <iostream>
#include "parser.h"
#include <utility>	// For move()

namespace utils = parser::utility;


AST *parser::parser(token::Token *current) {

	// Exit code for recursive Function. (End of Linked List)
	if(!current) return;

	// Next Token in Linked List.
	token::Token *next = current->getNext();
	// Previous Token in Linked List.
	token::Token *prev = current->getPrev();

	// Pointer to new AST node
	AST *newAST_Ptr = parser(next);

	// Instantiate AST_ID object and return to
	// previous Token in list.
	if(*current == token::IDENTIFIER) {
		// Calls R-Value Constructor to steal Dynamically allocated 
		// data from Token Object since we will no longer need Token.
		return (
			new class AST_ID(AST_ID, std::move(*current))
		);
	}

	// Instantiate AST_BinaryOp object and set values
	// equal to left and right AST Node pointers.
	if(*current == token::IS) {
		return (
			new AST_BinaryOp(		// Pass in previous Token given 
									// Linked List's nature of LIFO
				AST_IS, newAST_Ptr, parser::parseRightOperand(prev)
			)
		);
	}

	// Instantiate AST_List Object
	// It's value will be a Linked List 
	// of AST Nodes.
	if(utils::validStartToList(current)) {
		return (
									// Pass in previous Token given 
									// Linked List's nature of LIFO
			new AST_List(AST_LIST, parser::parseList(prev))
		)
	}

};


// Parser functions

AST *parser::parseRightOperand(token::Token tokenPtr) {

};

AST *parser::parseList(token::Token tokenPtr) {

};



// AST_List *parser::parseList()

// Utility Functions to help parse Tokens

bool utils::validStartToList(token::Token *tokenPtr) {

	token::Symbol tokenType = tokenPtr->getType();

	return tokenType == token::BAR;
};






