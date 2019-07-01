#include <iostream>
#include "Token.h"
#include "Queue.h"
#include "Lexer.h"
#include "Preparser.h"
#include "Parser.h"
#include "AST.h"
#include "OperatorStack.h"


void _log(AST *node) {

	if(!node) return ;

	_log(node->next); 


	std::cout << node->getTypeName() << std::endl << std::endl;

	

	if(*node == ast::ASSIGN) std::cout <<  "ADRESS " << node <<std::endl;


	

};

int main(){

	Queue<Token *> *tokenQ = lexer::lexer("new.vnm");

	Preparser *preparser = new Preparser(tokenQ);
	
	/*
	 	 *************************************** Passing Lambda to Lambda to know when
	 	 *************************************** to stop iterating over tokenQ.
	*/
	Queue<astPtr_t> *preparsedAst = preparser()([tokenQ]{return tokenQ->current();});

	AST *astHead = Preparse(tHead);

	AST *parsedAstHead = parser::_main(astHead);

	opStack->processEach();



	_log(parsedAstHead);

};

