#include <iostream>
#include "Token.h"
#include "lexer.h"
#include "parser.h"
#include "AST.h"

// void _log(AST *node) {

// 	if(!node) return ;

// 	_log(node->next);

// 	_log(node->node->getValue());

// 	std::cout << node->value->getTypeName(node->value->getType()) << std::endl;

// 	if(node->value->getName())
// 		std::cout << node->value->getName() << std::endl;

// };

int main(){

	token::TokenNode *tHead = lexer::lexer((char *) "new.vnm");

	AST *astHead = parser::parse(tHead);

	// _log(astHead);

	



};

