#ifndef AST_BLOCK_H

#define AST_BLOCK_H


#include "AST_Node.h"



class AST_Block : public AST_Node {

private:

	AST *value;


public:

	AST_Block(ast::AST_SYMBOL type, AST *value);


	void setValue(AST *value);

	AST *getValue() const;


}; // AST_Block



#endif