#include "AST_ID.h"

AST_ID::AST_ID(ast::AST_SYMBOL type, AST_Node *value) 
	:AST_Node(type), value(value)
{};