#include <iostream>
#include "parser.h"
#include <utility>	// For move()

namespace utils = parser::utility;



// IMPLEMENT PARSE PARAMS AND PARSE BLOCK FUNCTIONS


// Parser functions

AST_Node *parser::wrapperParser(token::Token *current) {

	// Exit code for recursive Function. (End of Linked List)
	if(!current) return nullptr;

	// Pointer to next AST node
	AST_Node *nextNode = wrapperParser(current->getNext());

	AST_Node *newNode = parser::parser(current);

	if(!newNode) return nextNode;

	newNode->setNext(nextNode);

	return newNode;

};

AST_Node *parser::parser(token::Token *tokenPtr) {

	// Parse Token and return the AST node 
	// the function below produces.

	AST_Node *newNode = nullptr;

	if(*tokenPtr == token::IS) 
		newNode = parseToken(tokenPtr);

	return newNode;
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


	// Return List or Function

	// Instantiate AST_List Object
	// It's value will be a Linked List 
	// of AST Nodes.
	if(utils::validStartToListOrParams(current)) {

		bool isParams = false;
		token::Token *startToBlock = nullptr;


		AST_Node *listValue = parser::parseListOrParams(prev, isParams, startToBlock);
		
		AST_Node *list = new AST_List(AST_LIST, listValue);

		if(isParams) {
			return AST_Function(
				AST_FUNCTION, list, parser::parseBlock(startToBlock->getPrev())
			);
		}
		else
			return list;


	}


	return nullptr;
};


// Parse operands of an AST operator node
AST_Node *parser::parseOperand(token::Token *tokenPtr) {
	return parser::parseToken(tokenPtr);

};


// Parse List of an AST list node
AST_Node *parser::parseListOrParams(token::Token *tokenPtr, bool &isParams, token::Token *&startToBlock) {

	if(*tokenPtr == token::BAR) {
		if(utils::validStartToFunctionBlock(tokenPtr->getPrev())) {
			isParams = true;
			startToBlock = token->getPrev()->getPrev();
		}
		return nullptr;	
	} 

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

//funct is |num, age| -> ` num is 5 `
// `5 is num ` -> |age, num| is funct 


// Parse statement block
AST_Node *parser::parseBlock(token::Token *tokenPtr) {

	// Exit code for recursive Function. (End of Block)
	if(*tokenPtr == token::BACKTICK) return nullptr;

	AST_Node *newNode = parser::parser(tokenPtr);

	// Pointer to next AST node
	AST_Node *nextNode = parseBlock(tokenPtr->getPrev());

	if(!newNode) return nextNode;

	newNode->setNext(nextNode);


	return newNode;
};



// Utility Functions to help parse Tokens

bool utils::validStartToListOrParams(token::Token *tokenPtr) {

	return(*tokenPtr == token::BAR);
};

bool utils::validStartToFunctionBlock(token::Token *tokenPtr) {
	return(
		(*tokenPtr == token::ARROW) && (*(tokenPtr->getNext()) == token::BACKTICK)
	);
}






