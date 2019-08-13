#include <iostream>
#include <utility>   // For forward, move
#include "Parser.h"
#include "../ast/AST.h"







/*
 +++++ Main C'Tor +++++
 */

Parser::Parser(std::vector<Token> &tokensVec_Param)
	:tokensVec(tokensVec_Param), curr(0), tokensVecLen(tokensVec_Param.size())
{};


/*
 +++++ ACCESSORS +++++
 */

std::vector<Token>::size_type Parser::getCurr() {
	return curr;
}




/*	
	*
	* Returns a callable that returns whether if at end of BLOCK or LIST range.
	* Lambda wrapped in function for reuse by LIST and BLOCK.
	*
*/
decltype(auto) Parser::endOfListAndBlockCallable() {

	/*
	 +++++ Get end of List or Block +++++
	 */
    decltype(tokensVec.size()) matchingIndx = tokensVec[curr].getMatchingPair();

	const Token &matchingPair = tokensVec[matchingIndx];

	return [this, &matchingPair] {

		return (

			/*
			 +++++ Check if end of Block or List has been reached. +++++
			 */

			&tokensVec[curr] != &matchingPair
		);
	};
};


/*
 +++++ Recursively parses Block or List value that is used to construct a Block +++++
 +++++ or List. May be body to a function, param list, object, array, etc.      +++++
 */

std::vector<ast_t> &Parser::parseRange() {

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
 +++++ Parse Token to an AST and Insert into Vector +++++
 */
void Parser::fillAstVecWithParsedToken(std::vector<ast_t> *astVecPtr) {


	/*
	 +++++ Identifier +++++
	 */
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

		astVecPtr->emplace_back(std::in_place_type< AST<Block> >, &parseRange()); 


	/*
	 +++++ Function +++++
	 */

	else if(tokensVec[curr] == Token::BAR) {

		/*
		 +++++ TODO: Maybe listValPtr should not be ast_t and have its own since you cant have some types in a List +++++
		 */

		/*
		 +++++ Parse parameter list +++++
		 */

		std::vector<ast_t> *listValPtr = &parseRange();

		/*
		 +++++ Shift pointer to skip closing Bar Token +++++
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
		std::vector<ast_t> *blockValPtr = &parseRange();

		/*
		 +++++ Push AST<Func> in vector. Vector creates AST<Func> emplace. AST creates  +++++
		 +++++     Func emplace. Func creates listValPtr and blockValPtr emplace.	    +++++
		 */

		astVecPtr->emplace_back(std::in_place_type< AST<Func> >, listValPtr, blockValPtr);

	}

	/*
	 +++++ Assignment operator +++++
	 */

	else if(tokensVec[curr] == Token::IS) {

		/*
		 +++++ Shift tokensVec ptr to rValue +++++
		 */
		++curr;

		/*
		 +++++ Insert parsed rValue token in the astVec. +++++
		 */
		fillAstVecWithParsedToken(astVecPtr);

		/*
		 +++++ Check if rValue is part of expression +++++
		 */
		if( (curr+1) < tokensVecLen  && tokensVec[curr+1] == Token::ADD) { // TODO: Make it work for all operators.

			/*
			 +++++ Shift pointer to operator Token +++++
			 */
			++curr;

			/*
			 +++++ Recursively parse expression +++++
			 */
			fillAstVecWithParsedToken(astVecPtr);
		}


		/*
		 +++++ Get left and right operands from ast vector. Last element is right operand of Assignment operator +++++
		 */
		ast_t &rOperand = *(--astVecPtr->end()),
			  &lOperand = *(astVecPtr->end() - 2);

		/*
		 +++++ lOperand and rOperand are expiring (popped off or replaced). Move C'Truct values in ASSIGN. +++++
		 +++++ AST creates ASSIGN emplace. Move Assign lOperand position to expiring AST<ASSIGN> object.   +++++   
		 */
		*(astVecPtr->end() - 2) = AST<Assign>(std::move(lOperand), std::move(rOperand));

		/*
		 +++++ Pop off rOperand +++++
		 */	
		astVecPtr->pop_back();
	}
	/*
	 +++++ Addition operator +++++ // [ID, Func()]
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
			  &lOperand = *(astVecPtr->end() - 2); 

		/*
		 +++++ lOperand and rOperand are expiring (popped off or replaced). Move C'Truct values in ADD. +++++
		 +++++ AST creates ADD emplace. Move Assign lOperand position to expiring AST<ADD> object.      +++++   
		 */
		*(astVecPtr->end() - 2) = AST<Add>(std::move(lOperand), std::move(rOperand));

		/*
		 +++++ Pop off rOperand +++++
		 */	
		astVecPtr->pop_back();

		/*
		 +++++ Check if rOperand is part of expression +++++
		 */
		if( (curr+1) < tokensVecLen  && tokensVec[curr+1] == Token::ADD) { // TODO: Make it work for all operators.
			/*
			 +++++ Shift pointer to operator Token +++++
			 */
			++curr;

			/*
			 +++++ Recursively parse expression +++++
			 */
			fillAstVecWithParsedToken(astVecPtr);

		}
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

		astVecPtr->emplace_back(std::in_place_type< AST<List> >, &parseRange()); 

	}

	else if(tokensVec[curr] == Token::STRING) {

		/*
		 +++++ Steal data from Token and C'truct AST<Str>. Vector creates AST<Str> emplace. AST creates Str emplace. +++++
		 */
		astVecPtr->emplace_back(std::in_place_type< AST<Str> >, std::move(tokensVec[curr]));
	}

	return;

}; // fillAstVecWithParsedToken











