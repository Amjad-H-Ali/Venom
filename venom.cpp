#include <iostream>
#include "Token.h"
#include "lexer.h"
#include "preparser.h"
#include "AST.h"

// void _log(AST *node) {

// 	if(!node) return ;

// 	_log(node->next);

// 	std::cout << node->node->getTypeName() << std::endl;



// };

int main(){

	token::TokenNode *tHead = lexer::lexer((char *) "new.vnm");

	AST *astHead = preparser::preparse(tHead);

	// _log(astHead);

};

