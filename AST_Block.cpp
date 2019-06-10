#include "AST_Block.h"

AST_Block::AST_Block(ast::AST_SYMBOL type, AST *value)
	:AST_Node(type), value(value)
{};


void AST_Block::setValue(AST *value) {
	this->value = value;
};
