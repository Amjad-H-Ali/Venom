#ifndef AST_LIST_H

#define AST_LIST_H

#include "AST.h"
#include "AST_Node.h"


class AST_List : public AST_Node {

private:

	AST *value;


public:

	AST_List(ast::AST_SYMBOL type, AST *value);

}; // AST_List



#endif