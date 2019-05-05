#include "AST_Node.h"

AST_Node::AST_Node(AST_SYMBOL type) 
	:this->type(type), this->next(nullptr)
{};

AST_SYMBOL AST_Node::getType() const {
	return this->type;
};

AST_Node AST_Node::getNext() const {
	return this->next
};

void AST_Node::setNext(AST_Node AST_NodePtr) {
	this->next = AST_NodePtr;
};