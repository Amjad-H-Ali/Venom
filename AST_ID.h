#pragma once

#include "AST.h"
#include "Token.h"

class AST_ID : public AST{
private:
	char *name;
public:
	AST_ID(AST_SYMBOL type, token::Token &&tokenNode); 
};