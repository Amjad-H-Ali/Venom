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
	Queue<Token> *tokensQ;

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
	void generateTokensInQ(std::string::size_type start = 0, std::string::size_type end = 0);


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
	void insertDimension(SharedPtr<Token> &tokenPtr);


public:

	/*
	 ++++++++++ Main C'tor ++++++++++++++
	*/

	Lexer(const char *fileName);

	Queue<Token> *Tokenize();

}; // Lexer



#endif
