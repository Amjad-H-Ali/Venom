#include <iostream>
#include <variant>
#include "AST.h"
#include "AST_Node.h"
#include "AST_STR.h"
#include "AST_List.h"
#include "AST_ID.h"
#include "AST_Block.h"
#include "AST_BinOp.h"
#include "AST_Func.h"	
#include "parser.h"
#include "OperatorStack.h"

AST{LIST{AST{}}}-AST{BLOCK{AST{}}}


AST{FUNC{LIST{AST}, BLOCK{AST}}}


OperatorStack *opStack = new OperatorStack;

AST *parser::_main(AST *astHead) {



	if(!astHead) return nullptr;

	AST *head = _main(astHead->next);

	astPtr_t astPtr = parser::parse(astHead, astHead->node);

	if(!astPtr) return head;

	AST *newAST = new AST;

	newAST->node = astPtr;

	newAST->next = head;

	if(head) head->prev = newAST;

	head = newAST;

	if(*newAST == ast::ASSIGN) opStack->push(newAST);

	return head;

};

template<typename ... Params>
astPtr_t parser::parse (AST *parent, Params&& ... params) {

	return std::visit(AstOverloads{

		[parent](AST_List *list)->astPtr_t {return parseListContext(parent);},

		[parent](AST_List *list, AST_Block *block)->astPtr_t {

			// Parsed block contents.
			AST *funcBody = parser::_main(block->getValue());

			// Steal list contents for function parameter list.
			return new AST_Func(ast::FUNC, std::move(*list), block);

		},

		[parent](AST_List *list, auto)->astPtr_t {return list;},

		[parent](AST_BinOp *binOp)->astPtr_t {return binOp;},

		[parent](auto, auto)->astPtr_t {return nullptr;},

		[parent](auto n)->astPtr_t {return n;},

		[parent](AST_Block *)->astPtr_t {return nullptr;}

	}, std::forward<Params>(params)...);

};

astPtr_t  parser::parseListContext(AST *parentOfList) {

  	AST *nextParent = parentOfList->prev;

  	return nextParent ? parser::parse(nextParent, parentOfList->node, nextParent->node) 
		: parser::parse(nextParent, parentOfList->node, (astPtr_t) nullptr);
};

AST_Block *parser::parseBlock(AST_Block *block) {

	// TODO: Clean up the memory leak here...
	
	AST *newAST = parser::_main(block->getValue());

	block->setValue(newAST);

	return block;
}


