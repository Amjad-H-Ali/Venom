
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
auto Preparser::endOfListAndBlockCallable() {

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
	auto isEndOfBlock = endOfListAndBlockCallable();

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
	auto getVecOfParsedBlockVal = (*this)();



	std::vector<ast_t> &blockVal = getVecOfParsedBlockVal(isEndOfBlock);

	/*
	 +++++ Shift pointer to exit Block +++++
	 */
	++curr;

	return blockVal;
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
	return [astVecPtr](auto isEndOfRange)->std::vector<ast_t>& {



		while(isEndOfRange()) {

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
		 +++++ Steal string value from Token and create ID. Vector creates AST<ID> emplace. AST creates ID emplace . +++++
		 */

		astVecPtr->emplace_back(std::in_place_type< AST<ID> >, std::move(tokensVec[curr]));

	/*
	 +++++ Start to Block +++++
	 */
	else if(tokensVec[curr] == Token::LHANDLE) {

		/*
		 +++++ Recursively parse Block value as vector. Vector creates AST<Block> emplace. AST creates Block emplace. +++++
		 */

		astVecPtr->emplace_back(std::in_place_type< AST<Block> >, parseBlockValue()); 
	};

	/*
	 +++++ Function Block +++++
	 */
	else if(tokensVec[curr] == Token::ARROW) {

		/*
		 ++++ Must be a param list preceding ARROW. Retrieve from ast vector. +++++
		 */

		ast_t &paramListAST = *(--astVecPtr.end());

		/*
		 +++++ Shift from ARROW to the next Token, which should be start to Block +++++
		 */

		++curr;

		/*
		 +++++ Get List from ast_t +++++
		 */

		AST<List> &paramList = std::get< AST<List> >(paramListAST);

		/*
		 +++++ Recursively parse Block value and Instantiate a Block. Then Instanstiat AST<Block> emplace +++++
		 */
		

		astVecPtr->emplace_back(Block(parseBlockValue())); 
		
	}

	/*
	 +++++ Function Parameter List +++++
	 */

	else if(tokensVec[curr] == Token::BAR && !tokensVec[curr].closing) {

		/*
		 +++++ Used to stop loop. When called, checks if iterator is at end of List range in tokensVec +++++ 
		 */

		auto isEndOfList = endOfListAndBlockCallable();

		/*
		 +++++ Shift iterator to Enter the List +++++
		 */

		++curr;


		auto getVecOfParsedListVal = (*this)();


		/*
		 +++++ TODO: Maybe listVal should not be ast_t and have its own since you cant have some types in a List +++++
		 */

		std::vector<ast_t> &listVal = getVecOfParsedListVal(isEndOfList);

		/*
		 +++++ Shift iterator to Skip Closing Token of List +++++
		 */

		++curr;

		/*
		 +++++ TODO: Maybe check if next Token is ARROW. Otherwise syntax error +++++
		 */

		/*
		 +++++ Shift iterator to Skip ARROW +++++
		 */

		++curr;

		/*
		 +++++ TODO: Maybe check if next Token is LHANDLE. Otherwise syntax error +++++
		 */


		/*
		 +++++ Parse Function Body +++++
		 */
		std::vector<ast_t> &blockVal = parseBlockValue();


		astVecPtr->emplace_back(std::in_place_type< AST<Func> >, listVal, blockVal);

	}


	else if(tokensVec[curr] == Token::IS)

		astVecPtr->emplace_back(BinOp()); 


	/*
		*
		* For array LIST and function parameter LIST.
		*
	*/
	else if(tokensVec[curr] == Token::LBRACKET) {

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








