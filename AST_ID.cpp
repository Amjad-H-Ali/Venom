#include "AST_ID.h"


AST_ID::AST_ID(AST_SYMBOL type, token::Token &&tokenNode) 
	:AST(type), name(tokenNode.getName())  
{	
	// Sets Token Node's name to nullptr
	// after stealing it.
	tokenNode.setName();
};