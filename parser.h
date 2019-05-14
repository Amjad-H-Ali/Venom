#pragma once
#include "AST.h"
#include "AST_List.h"
#include "AST_ID.h"
#include "AST_BinaryOp.h"
#include "AST_Function.h"
#include "Token.h"


namespace parser {

namespace utility {

	bool validStartToListOrParams(token::Token *tokenPtr);

	bool validStartToFunctionBlock(token::Token *tokenPtr);

}; // utility



	// Parser functions

	// Main parser
	AST_Node *wrapperParser(token::Token *current);

	AST_Node *parser(token::Token *tokenPtr) ;

	// Takes in a Token from a Linked List and Parses it.
	// Returns an AST Node.
	AST_Node *parseToken(token::Token *current);

	// Parse operands of an AST operator node
	AST_Node *parseOperand(token::Token *tokenPtr);

	// Parse List of an AST list node
	AST_Node *parseListOrParams(token::Token *tokenPtr, bool &isParams, token::Token *&startToBlock);

	// Parse List
	AST_Node *parseList(token::Token *tokenPtr);

	// Parse parameters
	AST_Node *parseParams(token::Token *tokenPtr);

	// Parse statement block
	AST_Node *parseBlock(token::Token *tokenPtr);


}; // parser