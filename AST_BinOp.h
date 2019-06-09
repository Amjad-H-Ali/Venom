#ifndef AST_BIN_OP_H

#define AST_BIN_OP_H

#include "AST_Node.h"


class AST_BinOp : public AST_Node {

private:

	AST_Node *left, *right;


public:

	AST_BinOp(ast::AST_SYMBOL type);

}; // AST_BinOp



#endif