#ifndef AST_ID_H

#define AST_ID_H

#include "AST_Node.h"


class AST_ID : public AST_Node {

private:

	char *name;

	AST_Node *value;


public:

	AST_ID(ast::AST_SYMBOL type, AST_Node *value);

}; // AST_ID



#endif