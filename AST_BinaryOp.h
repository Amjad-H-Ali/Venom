#pragma once

#include "AST.h"

class AST_BinaryOp : public AST {
private:
	AST *leftValue;
	AST *rightValue;
public:
	AST_BinaryOp(AST_SYMBOL type, AST *left, AST *right);
	
};