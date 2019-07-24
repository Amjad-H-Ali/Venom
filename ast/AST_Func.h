#ifndef AST_FUNC_H

#define AST_FUNC_H

#include "AST.h"
#include "AST_Node.h"
#include "AST_List.h"
#include "AST_Block.h"



class AST_Func : public AST_Node {

private:

	AST  *params;

	AST *body;


public:

	AST_Func(ast::AST_SYMBOL type, AST_List &&params, AST *body);

	void setValue(AST *params, AST *body);

	AST *getBody() const;



}; // AST_Func



#endif