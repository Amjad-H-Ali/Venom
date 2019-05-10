#include "AST.h"

AST_Node::AST_Node(AST_SYMBOL type) 
	:type(type), next(nullptr)
{};

AST_SYMBOL AST_Node::getType() const {
	return this->type;
};

AST_Node *AST_Node::getNext() const {
	return this->next;
};

void AST_Node::setNext(AST_Node *ASTPtr) {
	this->next = ASTPtr;
};