#include "AST_Func.h"

AST_Func::AST_Func(ast::AST_SYMBOL type, AST_List &&params, AST *body) 
	:AST_Node(type), params(params.getValue()), body(body)
{
	// Set value to nullptr after stealing.
	params.setValue(nullptr); 
};



void AST_Func::setValue(AST *params, AST *body) {
	this->params = params;
	this->body = body;
};

AST *AST_Func::getBody() const {

	return this->body;
};