#include "AST_ID.h"

AST_ID::AST_ID(token::Token &&tokenNode) {
	this->name = tokenNode->getName();
	tokenNode->setName(nullptr);
};