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
	
	// Parse current Token and return the AST node 
	// the function below produces.
	return parseToken(current, prev, next);	

};


/*
	* Parses Tokens.
	* Params: Current Token, Previous Token, and Next Token in Linked List
	* Defualt Params: Previous Token and Next Token.
	* Return: An AST Node.
*/
AST *parser::parseToken(
	token::Token *current, token::Token *prev=nullptr, token::Token *next=nullptr
) 

{
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

// Parse right operand of an AST operator node
AST *parser::parseRightOperand(token::Token tokenPtr) {
	// SHOULD CALL SPECIAL PORTION OF PARSER
	// PARSE LIST WILL BE CALLED, RETURNING AN AST NODE
};

// Parse List of an AST list node
AST *parser::parseList(token::Token tokenPtr) {
	if(*tokenPtr == token::BAR) return nullptr;

	// Recursively Parse each Token in List
	// When closing BAR is reached, headInList 
	// is set to nullptr.
	AST *headInList = parser::parseList(tokenPtr->getPrev());

	// Instantiate an AST object out of  current Token
	// and set its 'next' data member to whatever headInList
	// is pointing to. Return the AST node (headInList).
	return (parser::parseToken(tokenPtr)->setNext(headInList));

};



// AST_List *parser::parseList()

// Utility Functions to help parse Tokens

bool utils::validStartToList(token::Token *tokenPtr) {

	return(*tokenPtr == token::BAR);
};






