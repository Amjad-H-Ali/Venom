#include "AST_BinaryOp.h"

AST_BinaryOp::AST_BinaryOp(AST_SYMBOL type, AST *left, AST *right)
	:AST(type), leftValue(left), rightValue(right)
{};