#pragma once

#include "AST.h"

class AST_BinaryOp : public AST_Node {
private:
	AST_Node *leftValue;
	AST_Node *rightValue;
public:
	AST_BinaryOp(AST_SYMBOL type, AST_Node *left, AST_Node *right);
	
};