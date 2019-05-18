#include <iostream>
#include "Token.h"
#include "lexer.h"
#include "parser.h"
#include "AST.h"


int main(){

	token::TokenNode *head = lexer::lexer((char *) "new.vnm");

	AST_Node *AST_Head = parser::wrapperParser(head);

	for(AST_Node *ptr = AST_Head; ptr; ptr = ptr->getNext()) {
		if(ptr->getRightOperand()->getType() == AST_FUNCTION)

			std::cout << ptr->getTypeName(ptr->getRightOperand()->getParams()->getType()) << std::endl;
	}


};

