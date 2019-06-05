#include <iostream>
#include "Token.h"
#include "lexer.h"
#include "parser.h"
#include "AST.h"


int main(){

	// token::TokenNode *tHead = lexer::lexer((char *) "new.vnm");

	

	// for(token::TokenNode *ptr = tHead; ptr; ptr = ptr->next) {
	// 	std::cout << ptr->tokenPtr->getTypeName() << " ADDRESS: " << ptr;

	// 	if(ptr->end)
	// 		std::cout << "  END: TRUE" << std::endl;
	// 	else
	// 		std::cout << "  END: FALSE" << std::endl;
	// }

	// ASTNode *astHead = parser::parse(tHead);

	// for(ASTNode *ptr = astHead; ptr; ptr = ptr->next)
	// 	std::cout << ptr->value->getTypeName(ptr->value->getType()) << std::endl;


};

