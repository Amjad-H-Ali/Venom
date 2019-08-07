
/*
 +++++ Main C'Tor +++++
 */

Preparser::Preparser(const std::vector<Token> &tokensVec_Param)
	:tokensVec(tokensVec_Param), curr(0)
{};



/*	
	*
	* Returns a callable that returns whether if at end of BLOCK or LIST range.
	* Lambda wrapped in function for reuse by LIST and BLOCK.
	*
*/
auto Preparser::isAtEndOfListOrBlock() {

	const Token *matchingPair = tokensVec[curr].matchingPair;

	return [this, matchingPair] {

		return (

			/*
			 +++++ Check if at end of Block or List +++++
			 */

			tokensVec[curr] != *matchingPair;
		);
	};
};


/*
 +++++ Recursively parses Block value that is used to construct a Block. +++++
 +++++ A Block may be a body to a function, if statement, object, etc.   +++++
 */

std::vector<ast_t> &Preparser::parseBlockValue() {

	/*
		*
		* Conditional for parsing the range of tokens that is the Block.
		*
	*/
	auto isEndOfBlock = isAtEndOfListOrBlock();

	/*
	 +++++ Shift pointer to enter Block +++++
	 */
	++curr;

	/*
		*
		* Call to this Functor.
		* Returns a Lambda that parses the tokensVec data member .
		*
	*/
	auto getVectorWithParsedBlockVal = (*this)();

	return getVectorWithParsedBlockVal(isEndOfBlock);
}

/*
	*
	* Overload () operator. Creates a Queue of ast_t(s). 
	* Return: Lambda that takes in a conditional and parses Queue of tokenPtr(s)
	* and pushes parsed items into Queue of ast_t(s).
	*
*/
auto Preparser::operator()() {

	std::vector<ast_t> *astVecPtr = new std::vector<ast_t>;

	/*
		*
		* callableFlag: conditional to know when to stop iterating through
		* tokensVec member variable.
		*
	*/
	return [astVecPtr](auto callFlagToEnd)->std::vector<ast_t>& {



		while(callFlagToEnd()) {

			/*
				*
				* Parse token and push ast_t in container.
				*
			*/
			fillAstVecWithParsedToken(astVecPtr);

			/*
				*
				* Move "current" pointer one step ahead in tokensVec.
				*
			*/

			++curr;
		};

		return *astVecPtr;
	};
};


/*
	*
	* Parse token object and return an ast_t.
	*
*/
void Preparser::fillAstVecWithParsedToken(std::vector<ast_t> *astVecPtr) {


	if(tokensVec[curr] == Token::ID)

		/*
		 +++++ Steal string value from Token and create ID. Then create AST<ID> emplace. +++++
		 */

		astVecPtr->emplace_back( ID( std::move(tokensVec[curr]) ) );

	/*
	 +++++ Start to Block +++++
	 */
	else if(tokensVec[curr] == Token::LHANDLE) {

		/*
		 +++++ Recursively parse Block value and Instantiate a Block. Then Instanstiat AST<Block> emplace +++++
		 */
		astVecPtr->emplace_back(Block(parseBlockValue())); 
	};

	/*
	 +++++ Function Block +++++
	 */
	else if(tokensVec[curr] == Token::ARROW) {

		/*
		 ++++ Must be a param list preceding ARROW. Retrieve from ast vector. +++++
		 */

		ast_t &paramList = *(--astVecPtr.end());

		/*
		 +++++ Shift from ARROW to next Token, which should be start to Block +++++
		 */

		++curr;


		parseBlock()
	}


	else if(tokensVec[curr] == Token::IS)

		astVecPtr->emplace_back(BinOp()); 


	/*
		*
		* For array LIST and function parameter LIST.
		*
	*/
	else if(tokensVec[curr] == Token::LBRACKET || (tokensVec[curr] == Token::BAR && !tokensVec[curr].closing)) {

		/*
			*
			* Conditional for parsing the range of tokens that is the List.
			*
		*/
		auto callFlag = callFlagForListAndBlock(tokenPtr); 

		/*
		 +++++ Shift pointer to enter List +++++
		 */
		++curr;

		/*
			*
			* Call to this Functor.
			* Returns a Lambda that parses the tokensVec data member .
			*
		*/
		auto parseList = (*this)();

		

		astVecPtr->emplace_back( List(parseList(callFlag)) );

	};

	else if(tokensVec[curr] == Token::STRING)

		/*
			*
			* Steal STRING value from token object.
			*
		*/
		astVecPtr->emplace_back(Str(std::move(tokensVec[curr])));

	return;

}; // parserToken








