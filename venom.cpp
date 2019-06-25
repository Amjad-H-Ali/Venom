#include <iostream>
#include "Token.h"
#include "lexer.h"
#include "AST.h"
#include "preparser.h"
#include "parser.h"
#include "OperatorStack.h"


void _log(AST *node) {

	if(!node) return ;

	_log(node->next); 


	std::cout << node->getTypeName() << std::endl << std::endl;

	

	if(*node == ast::ASSIGN) std::cout <<  "ADRESS " << node <<std::endl;


	

};

int main(){

	token::TokenNode *tHead = lexer::lexer((char *) "new.vnm");

	AST *astHead = preparser::preparse(tHead);

	AST *parsedAstHead = parser::_main(astHead);

	opStack->processEach();



	_log(parsedAstHead);

};

