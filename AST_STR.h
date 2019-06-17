#ifndef AST_STR_H

#define AST_STR_H

#include "Token.h"
#include "AST_Node.h"



class AST_STR : AST_Node {

private:

	char *value;

public:
	/*	
		R-Value constructor:
		This constructor highjacks the name from an 
		expiring object of type Token.
	*/
	AST_STR(ast::AST_SYMBOL type, token::Token &&tkObj);

	void setValue(char *value);


}; // AST_STR



#endif