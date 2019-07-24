#include "AST_List.h"

AST_List::AST_List(ast::AST_SYMBOL type, AST *value) 
	:AST_Node(type), value(value)
{};


void AST_List::setValue(AST *value) {
	this->value = value;
};


AST *AST_List::getValue() const {
	
	return this->value;
};