#ifndef AST_ID_H

#define AST_ID_H

#include "AST_Node.h"
#include "Token.h"


class AST_ID : public AST_Node {

private:

	char *name;

	AST_Node *value;


public:
	/*	
		R-Value constructor:
		This constructor highjacks the name from an 
		expiring object of type Token.
	*/
	AST_ID(ast::AST_SYMBOL type, token::Token &&tkObj);

}; // AST_ID



#endif