
/*

[AST<ID>, AST<IS>, AST<Func>]

foo is |name| => :| |:

num is 1+2+3+4

[AST<ID>, AST<IS>, AST<NUM>, AST<ADD>, AST<NUM>, AST<ADD>, AST<NUM>, AST<ADD>, AST<NUM>]



*/


std::vector<ast_t> &astVec;

Parser::Parser(std::vector<ast_t> &astVecParam)
	:astVec(astVecParam)
{}


/*
 +++++ Creates new vector to store parsed elements. Takes in the Vector  +++++
 +++++ to parse. Returns Lambda that, when called, returns parsed vector +++++
 */
auto Parser::operator()(std::vector<ast_t> &astVecToParse) {

	std::vector<ast_t> *astVecPtr = new std::vector<ast_t>;

	return [&astVecToParse](){

		for(auto &astElem : astVecToParse)
	}

}


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



