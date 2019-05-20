#pragma once
#include "AST.h"
#include "AST_List.h"
#include "AST_ID.h"
#include "AST_BinaryOp.h"
#include "AST_Function.h"
#include "Token.h"

// Alias for const token::TokenNode *
typedef const token::TokenNode *tNode;


namespace parser {

namespace utility {

	bool validStartToListOrParams(tNode node);

	bool validStartToFunctionBlock(tNode node);

}; // utility



	// Parser functions

	// Main parser. Params: Linked-List Of Tokens.
	// AST_Node *wrapperParser(tNode current);
	// void wrapperParser();

	// AST_Node *parser(tNode node) ;

	// Takes in a Token from a Linked List and Parses it.
	// Returns an AST Node.
	AST_Node *parseToken(tNode current);

	// Parse operands of an AST operator node
	AST_Node *parseOperand(tNode node);

	// Parse List of an AST list node
	AST_Node *parseListOrParams(tNode node, bool &isParams, tNode &startToBlock);

	// Parse List
	AST_Node *parseList(tNode node);

	// Parse parameters
	AST_Node *parseParams(tNode node);

	// Parse statement block
	AST_Node *parseBlock(tNode node);


}; // parser