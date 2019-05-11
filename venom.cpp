#include <iostream>
#include "Token.h"
#include "lexer.h"
#include "parser.h"


int main(){

	lexer::Tokens *linkedList = lexer::lexer((char *) "new.vnm");

	token::Token *head = linkedList->tokenHead;

	parser::parser(head);


};

