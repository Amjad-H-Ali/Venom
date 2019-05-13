#include "AST_Function.h"

AST_Function::AST_Function(AST_SYMBOL type, AST *params, AST *block) 
	:AST_Node(type), parameters(params), block(block)
{};


// Accessor

AST *AST_Function::getParams() const {
	return this->parameters;
};
	
AST *AST_Function::getBlock() const {
	return this->block;
};