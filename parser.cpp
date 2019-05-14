#include <iostream>
#include "parser.h"
#include <utility>	// For move()

namespace utils = parser::utility;



// IMPLEMENT PARSE PARAMS AND PARSE BLOCK FUNCTIONS


// Parser functions

AST_Node *parser::parser(token::Token *current) {

	// Exit code for recursive Function. (End of Linked List)
	if(!current) return nullptr;

	// Pointer to next AST node
	AST_Node *nextNode = parser(current->getNext());

	
	// Parse current Token and return the AST node 
	// the function below produces.

	if(*current == token::IS) {

		AST_Node *newNode = parseToken(current);

		newNode->setNext(nextNode);
		return newNode;
	}

	return nextNode;

};


// Takes in a Token from a Linked List and Parses it.
// Returns an AST Node.
AST_Node *parser::parseToken(token::Token *current) {
	// Next Token in Linked List.
	token::Token *next = current->getNext();
	// Previous Token in Linked List.
	token::Token *prev = current->getPrev();



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
	// and parse right and left operands.
	if(*current == token::IS) {

		return (
			new AST_BinaryOp(		               // Pass in previous Token given 
									               // Linked List's nature of LIFO
				AST_IS, parser::parseOperand(next), parser::parseOperand(prev)
			)
		);
	}

	// Instantiate AST_FUNCTION object and parse parameter
	// list and statement block
	if(*current == token::SKINNY_ARROW) {

		//func|name, address|->` `
		//   ``-> |address,name| func

		return (
			new AST_Function(

				AST_FUNCTION, parser::parseParams(next), parser::parseBlock(prev) 
			)
		);
	}


	// Instantiate AST_List Object
	// It's value will be a Linked List 
	// of AST Nodes.
	if(utils::validStartToList(current)) {

		bool isParams = false;
		token::Token *endOfList = nullptr;


		AST_Node *listValue = parser::parseListOrParams(prev, isParams, endOfList);
		
		AST_Node *list = new AST_List(AST_LIST, listValue);

	}


	return nullptr;
};


// Parse operands of an AST operator node
AST_Node *parser::parseOperand(token::Token *tokenPtr) {
	return parser::parseToken(tokenPtr);

};


// Parse List of an AST list node
AST_Node *parser::parseListOrParams(token::Token *tokenPtr, bool &isParams, token::Token *&endOfList) {

	if(*tokenPtr == token::BAR && *(tokenPtr->getPrev()) == token::SKINNY_ARROW) {
		isParams = true;
		endOfList = token	
	} 

	if(*tokenPtr == token::BAR) return nullptr;
		


	// Recursively Parse each Token in List
	// When closing BAR is reached, nextInList 
	// is set to nullptr.
	AST_Node *nextInList = parser::parseListOrParams(tokenPtr->getPrev());

	// Instantiate an AST object out of  current Token
	// and set its 'next' data member to whatever nextInList
	// is pointing to. Return the AST node.
	AST_Node *newNode = nullptr;

	if(*tokenPtr == token::COMMA)
		return nextInList;

	if(isParams)
		newNode = parser::parseParams(tokenPtr);
	else
		newNode = parser::parseList(tokenPtr);

	newNode->setNext(nextInList);

	return newNode;


};

// Parse List
AST_Node *parser::parseList() {
	if(*tokenPtr == token::IDENTIFIER || *tokenPtr == token::STRING)
		return parser::parseToken(tokenPtr);
	else
		//throw error: illegal object in array.
		return nullptr;
}

// Parse parameters
AST_Node *parser::parseParams(token::Token *tokenPtr) {
	if(*tokenPtr == token::IDENTIFIER)
		return parser::parseToken(tokenPtr);
	else
		//throw error: illegal object in params.
		return nullptr;
};	



// Utility Functions to help parse Tokens

bool utils::validStartToList(token::Token *tokenPtr) {

	return(*tokenPtr == token::BAR);
};






