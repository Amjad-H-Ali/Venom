#pragma once
#include "AST.h"

class AST_Function : public AST_Node {
private:
	AST *parameters;
	AST *block;

public:

	AST_Function(AST_SYMBOL type, AST *params, AST *block);

	// Accessors
	AST *getParams() const;
	AST *getBlock() const;
}; // AST_Function