#pragma once

#include "AST_Node.h"
#include "Token.h"

class AST_ID : public AST_Node {
private:
	char *name;
public:
	AST_ID(token::Token &&tokenNode);
};