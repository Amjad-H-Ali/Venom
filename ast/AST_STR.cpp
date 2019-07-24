#include "AST_STR.h"

/*
	R-Value constructor:
	This constructor highjacks the name from an 
	expiring object of type Token.
*/
AST_STR::AST_STR(ast::AST_SYMBOL type, token::Token &&tkObj)
	:AST_Node(type), value(tkObj.getName())
{
	tkObj.setName(); // Set "name" to nullptr in Token object.
};


void AST_STR::setValue(char *value) {

	this->value = value;
};