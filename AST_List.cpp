#include "AST_List.h"


AST_List::AST_List(AST_SYMBOL type, AST_Node *AST_NodePtr)
	:AST_Node(type), this->value(AST_NodePtr)
{};

AST_Node* AST_List::getValue() const {
	return this->value;
};