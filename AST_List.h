#pragma once

#include "AST.h"

class AST_List : public AST_Node {
private:
	AST_Node *value;
public:
	AST_List(AST_SYMBOL type, AST_Node *ASTPtr);
	AST_Node *getValue() const;
}; // AST_List