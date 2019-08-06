#ifndef LEXER_H

#define LEXER_H



class Lexer {

private:

	std::ifstream inFile;

	std::string stream;

	/*
		*
		* Tokens are stored here and will be fed to the Preparser.
		*
	*/
	std::vector<Token> *tokensVecPtr;

	/*	
		*
		* Represents Dimensions of an array.
		*
	*/
	ArrayDimension *const arrayD;

	/*	
		*
		* Represents Dimension of a block.
		*
	*/
	BlockDimension *const blockD;

	/*
		*
		* Represents Dimension of a parameter list.
		*
	*/
	ParamDimension *const paramD;

	/*
	 +++++ Finds corresponding Token symbol of a string from input stream in O(1) time-complexity. +++++
	 */

	static Trie<Token::Symbol> mapToSymbol;

	/* 
		*
		* Gets the index of the stream where it no longer can be 
		* part of a potential identifier. 
		* Params: start position to read the stream (defualt to beginning).
		*
    */
	std::string::size_type getIdentifierBreakPoint(std::string::size_type start = 0);

	/*
		*
		* Gets the ending index of the string in stream.
		* Params: start position to read the stream (defualt to beginning).
		*
	*/
	std::string::size_type getStrBreakPoint(std::string::size_type start = 0);

	/*
		*
		* Tokenizes data from stream and places it in tokensQ.
		*
	*/
	void generateTokensInVec(std::string::size_type start = 0, std::string::size_type end = 0);


	/*	
		* 
		* Checks if symbol is of an opening/closing to array,
		* block, or parameter list.
		*
	*/
	inline bool isDimensional(Token::Symbol sym); 

	/*
		*
		* Inserts opening/closing Token of block, array or
		* parameter list.
		*
	*/
	void insertDimension(const Token &token);


public:

	/*
	 ++++++++++ Main C'tor ++++++++++++++
	*/

	Lexer(const char *fileName);

	std::vector<Token> &operator ()();

}; // Lexer



#endif
