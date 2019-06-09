#include "AST_List.h"

AST_List::AST_List(ast::AST_SYMBOL type, AST *value) 
	:AST_Node(type), value(value)
{};
