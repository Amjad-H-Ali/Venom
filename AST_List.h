#pragma once

#include "AST.h"

class AST_List : public AST {
private:
	AST *value;
public:
	AST_List(AST_SYMBOL type, AST *ASTPtr);
	AST* getValue() const;
};