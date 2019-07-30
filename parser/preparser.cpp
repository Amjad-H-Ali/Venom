







Preparser::Preparser(const Queue<Token> *tokensQ_Param)
	:tokensQ(tokensQ_Param)
{};



/*	
	*
	* Returns a callable that returns whether if at end of BLOCK or LIST range.
	* Lambda wrapped in function for reuse by LIST and BLOCK.
	*
*/
auto Preparser::callFlagForListAndBlock(Token *tokenPtr) {

	return [tokenPtr, tokensQ] {

		return (

			tokenPtr->matchingCloseToken != tokensQ->current();
		);
	};
};


/*
	*
	* Overload () operator. Creates a Queue of ast_t(s). 
	* Return: Lambda that takes in a conditional and parses Queue of tokenPtr(s)
	* and pushes parsed items into Queue of ast_t(s).
	*
*/
auto Preparser::operator()() {

	Queue<ast_t> *preparsedAstQ = new Queue<ast_t>;

	/*
		*
		* callableFlag: conditional to know when to stop iterating through
		* tokensQ member variable.
		*
	*/
	return [](auto callableFlag) {

		while(callableFlag()) {

			/*
				*
				* Parse token and receive ast_t.
				*
			*/
			ast_t parsedAstPtr = parseToken(tokensQ->current());

			parsedAst->push(parsedAstPtr); 

			/*
				*
				* Move "_current" pointer one step ahead.
				*
			*/
			tokensQ->jump(1); 
		};

		return parsedAst;
	};
};


/*
	*
	* Parse token object and return an ast_t.
	*
*/
ast_t Preparser::parseToken(const SharedPtr<Token> &tokenPtr) {


	if(*tokenPtr == Token::ID)

		/*
			*
			* Steal Identifier name from token object.
			*
		*/
		return new AST_ID(ast::ID, std::move(*tokenPtr));

	/*
		*
		* Start to BLOCK.
		*
	*/
	if(*tokenPtr == Token::LHANDLE) {

		tokensQ->jump(1);

		/*
			*
			* Call to this Functor.
			* Returns a Lambda that parses the tokensQ data member .
			*
		*/
		auto parseBlock = (*this)();

		/*
			*
			* Conditional for parsing the range of tokens that is the Block.
			*
		*/
		auto callFlag = callFlagForListAndBlock(tokenPtr);

		/*
			*
			* Recursively parsing block. 
			*
		*/
		return new AST_BLOCK(ast::BLOCK, parseBlock(callFlag));
	};


	else if(*tokenPtr == Token::IS)

		return new AST_BinOp(ast::ASSIGN);


	/*
		*
		* For array LIST and function parameter LIST.
		*
	*/
	else if(*tokenPtr == Token::LBRACKET || (*tokenPtr == Token::BAR && !tokenPtr->closing)) {

		tokensQ->jump(1);

		/*
			*
			* Call to this Functor.
			* Returns a Lambda that parses the tokensQ data member .
			*
		*/
		auto parseList = (*this)();

		/*
			*
			* Conditional for parsing the range of tokens that is the List.
			*
		*/
		auto callFlag = callFlagForListAndBlock(tokenPtr); 

		return new AST_List(ast::LIST, parseList(callFlag));

	};

	else if(*tokenPtr == Token::STRING)

		/*
			*
			* Steal STRING value from token object.
			*
		*/
		return new AST_STR(ast::STR, std::move(*tokenPtr));

	return nullptr;

}; // parserToken








