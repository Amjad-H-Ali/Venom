#include <iostream>
#include "Token.h"
#include "lexer.h"
#include "parser.h"
#include "AST.h"


int main(){

	token::TokenNode *tHead = lexer::lexer((char *) "new.vnm");

	for(token::TokenNode *ptr = tHead; ptr; ptr = ptr->next) {
		std::cout << "TN:             "<< ptr->tokenPtr->getTypeName() << std::endl;

		if(*ptr == token::RBRACKET || *ptr == token::LBRACKET)
			std::cout << "BRACKET:             "<< ptr->matchingPair << std::endl;

	}

	// for(token::TokenNode *ptr = tHead; ptr; ptr = ptr->next) {
	// 	std::cout << ptr->tokenPtr->getTypeName() << " ADDRESS: " << ptr;

	// 	if(ptr->end)
	// 		std::cout << "  END: TRUE" << std::endl;
	// 	else
	// 		std::cout << "  END: FALSE" << std::endl;
	// }

	std::cout << "MAIN" << std::endl;

	std::cout << tHead->matchingPair->matchingPair << " " << tHead->tokenPtr->getTypeName() << std::endl;

	ASTNode *astHead = parser::parse(tHead);

	



};

