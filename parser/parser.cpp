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





OperatorStack *opStack = new OperatorStack;

AST *parser::_main(AST *astHead) {



	if(!astHead) return nullptr;

	AST *head = _main(astHead->next);

	ast_t astPtr = parser::parse(astHead, astHead->node);

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
ast_t &parser::parse (AST *parent, Params&& ... params) {

	return std::visit(AstOverloads {

		[parent](AST<List> *list)->ast_t &{return parseListContext(parent);},

		[parent](AST_List *list, AST_Block *block)->ast_t &{

			// Parsed block contents.
			AST *funcBody = parser::_main(block->getValue());

			// Steal list contents for function parameter list.
			return new AST_Func(ast::FUNC, std::move(*list), funcBody);

		},

		[parent](AST_List *list, auto)->ast_t &{return list;},

		[parent](AST_BinOp *binOp)->ast_t &{return binOp;},

		[parent](auto, auto)->ast_t &{return nullptr;},

		[parent](auto n)->ast_t &{return n;},

		[parent](AST_Block *)->ast_t &{return nullptr;}

	}, std::forward<Params>(params)...);

};

ast_t  parser::parseListContext(AST *parentOfList) {

  	AST *nextParent = parentOfList->prev;

  	return nextParent ? parser::parse(nextParent, parentOfList->node, nextParent->node) 
		: parser::parse(nextParent, parentOfList->node, (ast_t) nullptr);
};



