#include "AST_BinOP.h"

AST_BinOp::AST_BinOp(ast::AST_SYMBOL type, AST_Node *left, AST_Node *right)
	:AST_Node(type), left(left), right(right)
{};
