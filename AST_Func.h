#ifndef AST_FUNC_H

#define AST_FUNC_H

#include "AST_Node.h"
#include "AST_List.h"
#include "AST_Block.h"



class AST_Func : public AST_Node {

private:

	AST_List  *params;

	AST_Block *body;


public:

	AST_Func(ast::AST_SYMBOL type, AST_List *params, AST_Block *body);

	void setValue(AST_List *params, AST_Block *body);



}; // AST_Func



#endif