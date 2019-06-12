#include "AST_Func.h"

AST_Func::AST_Func(ast::AST_SYMBOL type, AST_List *params, AST_Block *body) 
	:AST_Node(type), params(params), body(body)
{};



void AST_Func::setValue(AST_List *params, AST_Block *body) {
	this->params = params;
	this->body = body;
};

