#include "AST_BinaryOp.h"

AST_BinaryOp::AST_BinaryOp(AST_SYMBOL type, AST_Node *left, AST_Node *right)
	:AST_Node(type), leftValue(left), rightValue(right)
{};