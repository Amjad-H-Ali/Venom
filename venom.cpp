#include <iostream>
#include "Token.h"
#include "lexer.h"
#include "parser.h"
#include "AST.h"


int main(){

	lexer::Tokens *linkedList = lexer::lexer((char *) "new.vnm");

	token::Token *head = linkedList->tokenHead;

	// TODO: DECIDE ON STRUCT OR THIS.
	// Declared in AST.h
	AST_Node *AST_Head = parser::wrapperParser(head);

	for(AST_Node *ptr = AST_Head; ptr; ptr = ptr->getNext()) {
		std::cout << ptr->getTypeName(ptr->getLeftOperand()->getType()) << std::endl;
	}


};

