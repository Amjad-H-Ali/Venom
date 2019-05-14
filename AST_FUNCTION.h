#pragma once
#include "AST.h"

class AST_Function : public AST_Node {
private:
	AST_Node *parameters;
	AST_Node *block;

public:

	AST_Function(AST_SYMBOL type, AST_Node *params, AST_Node *block);

	// Accessors
	AST_Node *getParams() const;
	AST_Node *getBlock() const;
}; // AST_Function