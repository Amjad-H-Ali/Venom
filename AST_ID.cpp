#include "AST_ID.h"

AST_ID::AST_ID(AST_SYMBOL type, token::Token &&tokenNode) 
	:AST(type), name(tokenNode.getName()) 
{
	tokenNode.setName(nullptr);
};