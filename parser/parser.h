#ifndef PARSER_H

#define PARSER_H

#include <vector>
#include "../lexer/token/Token.h"
#include "../ast/ast_t.h"

class Parser {

private:

	std::vector<Token> &tokensVec;

	decltype(tokensVec.size()) tokensVecLen;

	/*
	 +++++ For iterating tokensVec +++++
	 */

	decltype(tokensVec.size()) curr;

	/*	
		*
		* Returns a callable that returns whether at end of a BLOCK or LIST range.
		* Lambda wrapped in function for reuse by LIST and BLOCK.
		*
	*/
	decltype(auto) endOfListAndBlockCallable();

	/*
	 +++++ Recursively parses Block or List value that is used to construct a Block +++++
	 +++++ or List. May be body to a function, param list, object, array, etc.      +++++
	 */

	std::vector<ast_t> &parseRange();

	/*
	 +++++ Parse Token to an AST and Insert into Vector +++++
	 */
 	void fillAstVecWithParsedToken(std::vector<ast_t> *astVecPtr);

public:

	/*
	 +++++ Main C'Tor +++++
	 */
	Parser(std::vector<Token> &tokensVec_Param);


	/*
	 +++++ Used in main. Define here since it has deduced return type. +++++
	 */

	/*
		*
		* Overload () operator. Creates a Queue of ast_t(s). 
		* Return: Lambda that takes in a conditional and parses Queue of tokenPtr(s)
		* and pushes parsed items into Queue of ast_t(s).
		*
	*/
	decltype(auto) operator()() {

		std::vector<ast_t> *astVecPtr = new std::vector<ast_t>;

		/*
			*
			* callableFlag: conditional to know when to stop iterating through
			* tokensVec member variable.
			*
		*/
		return [this, astVecPtr](auto &&isEndOfRange)->std::vector<ast_t>& {



			while(isEndOfRange()) {

				/*
					*
					* Parse token and push ast_t in container.
					*
				*/
				fillAstVecWithParsedToken(astVecPtr);

				/*
					*
					* Shift "current" pointer one step ahead in tokensVec.
					*
				*/

				++curr;

				

			};

			return *astVecPtr;
		};

	} // operator()


	/*
	 +++++ ACCESSORS +++++
	 */

	std::vector<Token>::size_type getCurr();


}; // Parser

#endif