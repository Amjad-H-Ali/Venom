#include "AST.h"

AST::AST(AST_SYMBOL type) 
	:type(type), next(nullptr)
{};

AST_SYMBOL AST::getType() const {
	return this->type;
};

AST *AST::getNext() const {
	return this->next;
};

void AST::setNext(AST *ASTPtr) {
	this->next = ASTPtr;
};