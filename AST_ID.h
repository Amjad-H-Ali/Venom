#pragma once

#include "AST.h"
#include "Token.h"

class AST_ID : public AST_Node {
private:
	char *name;
public:
	// Pass by R-value constructor to steal dynamicly
	// allocated memory from Token Object that will 
	// expire. In this case we are deleting the Token 
	// Linked List after making the AST Link.
	AST_ID(AST_SYMBOL type, token::Token &&tokenNode); 
}; // AST_ID