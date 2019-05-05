#pragma once

#include "AST_Node.h"

class AST_List : public AST_Node {
private:
	AST_Node *value;
public:
	AST_List(AST_Node *AST_NodePtr);
	AST_Node* getValue() const;
};