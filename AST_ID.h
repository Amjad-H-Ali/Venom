#ifndef AST_ID_H

#define AST_ID_H


#include "Token.h"
#include "AST_Node.h"


class AST_ID : public AST_Node  {

private:

	char *value;



public:
	/*	
		R-Value constructor:
		This constructor highjacks the name from an 
		expiring object of type Token.
	*/
	AST_ID(ast::AST_SYMBOL type, token::Token &&tkObj);

	void setValue(char *value);


}; // AST_ID



#endif