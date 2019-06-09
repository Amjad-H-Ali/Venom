#include "AST_BinOp.h"

AST_BinOp::AST_BinOp(ast::AST_SYMBOL type)
	:AST_Node(type), left(nullptr), right(nullptr)
{};
