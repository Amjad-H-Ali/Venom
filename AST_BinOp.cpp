#include "AST_BinOp.h"

AST_BinOp::AST_BinOp(ast::AST_SYMBOL type)
	:AST_Node(type), left(nullptr), right(nullptr)
{};


void AST_BinOp::setValue(AST_Node *left, AST_Node *right) {
	this->left = left;
	this->right = right;
};
