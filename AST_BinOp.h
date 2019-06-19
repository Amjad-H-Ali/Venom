#ifndef AST_BIN_OP_H

#define AST_BIN_OP_H


#include "AST_Node.h"

class AST_BinOp : public AST_Node {

private:

	astPtr_t left, right;


public:

	AST_BinOp(ast::AST_SYMBOL type);

	void setValue(astPtr_t left, astPtr_t right);


}; // AST_BinOp



#endif