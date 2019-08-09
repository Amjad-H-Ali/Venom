
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

	const Token *matchingPairPtr = tokensVec[curr].matchingPair;

	return [this, matchingPairPtr] {

		return (

			/*
			 +++++ Check if end of Block or List has been reached. +++++
			 */

			&tokensVec[curr] != matchingPairPtr;
		);
	};
};


/*
 +++++ Recursively parses Block or List value that is used to construct a Block +++++
 +++++ or List. May be body to a function, param list, object, array, etc.      +++++
 */

std::vector<ast_t> &Preparser::parseRange() {

	/*
		*
		* Conditional for parsing the range of tokens that is the Block.
		*
	*/
	auto isEndOfRange = endOfListAndBlockCallable();

	/*
	 +++++ Shift pointer to enter Block or List +++++
	 */
	++curr;

	/*
		*
		* Call to this Functor.
		* Returns a Lambda that parses the tokensVec data member .
		*
	*/
	auto getVecOfParsedRange = (*this)();




	return getVecOfParsedRange(isEndOfRange);
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
	else if(tokensVec[curr] == Token::LHANDLE) 

		/*
		 +++++ Recursively parse Block value as vector. Vector creates AST<Block> emplace. AST creates Block emplace. +++++
		 */

		astVecPtr->emplace_back(std::in_place_type< AST<Block> >, parseRange()); 


	/*
	 +++++ Function Parameter List +++++
	 */

	else if(tokensVec[curr] == Token::BAR) {

		/*
		 +++++ TODO: Maybe listVal should not be ast_t and have its own since you cant have some types in a List +++++
		 */

		/*
		 +++++ Parse parameter list +++++
		 */

		std::vector<ast_t> &listVal = parseRange();


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
		std::vector<ast_t> &blockVal = parseRange();

		/*
		 +++++ Push AST<Func> in vector. Vector creates AST<Func> emplace. AST  +++++
		 +++++ creates Func emplace. Func creates listVal and blockVal emplace.	+++++
		 */

		astVecPtr->emplace_back(std::in_place_type< AST<Func> >, listVal, blockVal);

	}

	/*
	 +++++ Assignment operator +++++
	 */

	else if(tokensVec[curr] == Token::IS) {

		/*
		 +++++ Assign values set later in Parser +++++
		 */

		astVecPtr->emplace_back(std::in_place_type< AST<Assign> >); 

		/*
		 +++++ Shift tokensVec ptr to rValue +++++
		 */
		++curr;

		/*
		 +++++ Insert parsed rValue token to the astVec. +++++
		 */
		fillAstVecWithParsedToken(astVecPtr);

		/*
		 +++++ Check if rValue is part of expression +++++
		 */
		if(tokensVec[++curr] && tokensVec[curr] == Token::ADD) // TODO: Make it work for all operators.

			/*
			 +++++ Recursively parse expression +++++
			 */
			fillAstVecWithParsedToken(astVecPtr);
	}
	/*
	 +++++ Addition operator +++++ // [ID, 2, 3]
	 */
	else if(tokensVec[curr] == Token::ADD) {

		/*
		 +++++ Shift tokensVec ptr to right value +++++
		 */
		++curr;

		/*
		 +++++ Insert parsed right value token to the astVec. +++++
		 */
		fillAstVecWithParsedToken(astVecPtr);

		/*
		 +++++ Get left and right operands from ast vector. Last element is right operand of ADD operator +++++
		 */
		ast_t &rOperand = *(--astVecPtr->end()),
			  &lOperand = *(astVecPtr->end() - 3); 

		*(astVecPtr->end() - 3) = AST<ADD>(std::move(lOperand), std::move(rOperand));

		astVecPtr->emplace_back(std::in_place_type< AST<ADD> >, std::move(rOperand ))



	}




	/*
		*
		* For array LIST and function parameter LIST.
		*
	*/
	else if(tokensVec[curr] == Token::LBRACKET) {

		/*
		 +++++ Recursively parse List value as vector. Vector creates AST<List> emplace. AST creates List emplace. +++++
		 */

		astVecPtr->emplace_back(std::in_place_type< AST<List> >, parseRange()); 

	};

	else if(tokensVec[curr] == Token::STRING)

		/*
		 +++++ Steal data from Token and C'truct AST<Str>. Vector creates AST<Str> emplace. AST creates Str emplace. +++++
		 */
		astVecPtr->emplace_back(std::in_place_type< AST<Str> >, std::move(tokensVec[curr]));

	return;

}; // parserToken








