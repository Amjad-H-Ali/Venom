#include "AST_ID.h"

/*	
	R-Value constructor:
	This constructor highjacks the name from an 
	expiring object of type Token.
*/
AST_ID::AST_ID(ast::AST_SYMBOL type, AST_Node *value, token::Token &&tkObj) 
	:AST_Node(type), value(value)
{};