#pragma once
#include "AST.h"
#include "AST_List.h"
#include "AST_ID.h"
#include "AST_BinaryOp.h"
#include "AST_Function.h"
#include "Token.h"


namespace parser {

namespace utility {

	bool validStartToListOrParams(token::TokenNode *node);

	bool validStartToFunctionBlock(token::TokenNode *node);

}; // utility



	// Parser functions

	// Main parser. Params: Linked-List Of Tokens.
	AST_Node *wrapperParser(token::TokenNode *current);

	AST_Node *parser(token::TokenNode *node) ;

	// Takes in a Token from a Linked List and Parses it.
	// Returns an AST Node.
	AST_Node *parseToken(token::TokenNode *current);

	// Parse operands of an AST operator node
	AST_Node *parseOperand(token::TokenNode *node);

	// Parse List of an AST list node
	AST_Node *parseListOrParams(token::TokenNode *node, bool &isParams, token::TokenNode *&startToBlock);

	// Parse List
	AST_Node *parseList(token::TokenNode *node);

	// Parse parameters
	AST_Node *parseParams(token::TokenNode *node);

	// Parse statement block
	AST_Node *parseBlock(token::TokenNode *node);


}; // parser