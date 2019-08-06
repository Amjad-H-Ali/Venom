/* 
	*
	* Gets the index of the stream where it no longer can be 
	* part of a potential identifier. 
	* Params: start position to read the stream (defualt to beginning).
	*
*/
std::string::size_type Lexer::getIdentifierBreakPoint(std::string::size_type start = 0) {
	
	decltype(start) beginning = start;

	/*
		*
		* Identifier rules: 
		*   * Can contain anything from "A-Z", and "_".
		*   * Can contain numbers as long as it does not begin with one.
		* -------------------------------------------------------------
		* This loop increments as long as above conditions are met.
		*
	*/
	for(decltype(start) len = stream.size(); (start < len) && 
		((stream[start] >= 'a' && stream[start] <= 'z') || 
		(stream[start] >= 'A' && stream[start] <= 'Z') ||
		(stream[start] == '_') || ((start > beginning) && 
		(stream[start] >= '0') && (stream[start] <= '9'))); ++start);


	return start;
}

/*
	*
	* Gets the ending index of the string in stream.
	* Params: start position to read the stream (defualt to beginning).
	*
*/
std::string::size_type Lexer::getStrBreakPoint(std::string::size_type start = 0) {

	/*
		*
		* Store so we know which type of ending quote to look for. Increment
		* start to move on to firt character in string.
		*
	*/
	char quote = stream[start++];

	for(decltype(start) len = stream.size(); start < len && stream[start] != quote; ++start);

	return start;
}

/*
	*
	* Tokenizes data from stream and places it in tokensQ.
	*
*/
void Lexer::generateTokensInQ(std::string::size_type start = 0, std::string::size_type end = 0) {

	if(end == 0) end = stream.size();

    if(start >= end) return;

    /*
		*
		* Check if stream is the corresponding string value to any of the Token
		* symbols held in the Trie (mapToSymbol). This can be a keyword,
		* paranthesis, comma, bracket, etc.
		*
    */
    if(Token::Symbol *symPtr = mapToSymbol.map(stream, start, end)) {

    	tokensQ.emplace_back(*symPtr);

    	/*
			*
			* Check if symbol is opening/closing a dimension of a block, array,
			* or parameter list. If so, mark the Token that was just created.
			* tokensQ.end() returns SharedPtr to Token.
			*
    	*/
    	if(isDimensional(*symPtr)) insertDimension(*tokensQ.end());
    
        

    }
    
    /*
		*
		* If stream does not match any of the Token symbols, then it could be any of the following:
		*     +It's holding more than one symbol, meaning it contains symbols that were not spaced out (ie. "if(" ).
		*     +It's an identifier.
		* 	  +It's a string.
		* 	  +Otherwise, it's an error.
		* Reccusively Tokenize potential string, identifier, keyword, etc.
    */
    else {

    	/*
        	*
			* Check for possible string.
			*
        */
        if(stream[start] == '"' || stream[start] == '\'') {

        	decltype(start) strBreak = getStrBreakPoint(start);


        	tokensQ.emplace_back(stream.substr(start, strBreak), Token::STRING);

        	/*
        		*
        		* Increment to skip ending quote.
        		*
        	*/ 
        	start = (++strBreak);

        }

        else {

        	/*	
        		*
        		* If aToZbreak is greater than symBreak and symBreak was greater than 0,
        		* than we have an identifier whom part of it happens to have the same name 
        		* as a symbol (ie. Symbol: is, Identifier: isFoo)
        		*
	    	*/
	        decltype(start) aToZbreak = getIdentifierBreakPoint(start),
	                        symBreak  = mapToSymbol.getBreakPoint(stream, start);
	    
	        /*
	        	*
				* Check for possible match to keywords or other Symbols in Trie.
				*
	        */
	        if( (symBreak > 0) && (symBreak >= aToZbreak) ) {

	        	/*
	        		*
	        		* Tokenize symbol using the main if statement above 
	        		* and control retrurns here.
	        		*
	        	*/
	        	generateTokensInQ(start, symBreak);

	            start = symBreak;
	        }

	        /*
	        	*
				* Check for possible identifier.
				*
	        */
	        else if(aToZbreak > 0) {

	        	tokensQ.emplace_back(stream.substr(start, aToZbreak), Token::IDENTIFIER); 

	            start = aToZbreak;
	        }

	        /*
	        	*
	        	* else: error
	        	*
	        */
       	}

        generateTokensInQ(start, end);
    }
    
} // generateTokensInQ


/*	
	* 
	* Checks if symbol is of an opening/closing to array,
	* block, or parameter list.
	*
*/
inline bool Lexer::isDimensional(Token::Symbol sym) {

	return (

		sym == Token::LBRACKET || sym == Token::RBRACKET ||
		sym == Token::LHANDLE  || sym == Token::RHANDLE  ||
		sym == token::BAR 
	
	);
} 

/*
	*
	* Inserts opening/closing Token of block, array or
	* parameter list.
	*
*/
void Lexer::insertDimension(const Token &token) {

	if(token == Token::LBRACKET) {

		if(!arrayD) arrayD = ArrayDimension::getInstance();

		arrayD->insertOpen(token);
	}


	else if(token == Token::LHANDLE) {

		if(!blockD) blockD = BlockDimension::getInstance();

		blockD->insertOpen(token);
	}

	
	else if(*paramD == 0  && token == Token::BAR) {

		if(!paramD) paramD = ParamDimension::getInstance();

		paramD->insertOpen(token);
	}
	

	else if(token == Token::RBRACKET) 

		arrayD->insertClose(token);


	else if(token == Token::RHANDLE)

		blockD->insertClose(token);


	else if(token == Token::BAR) 
		
		paramD->insertClose(token);
	
};

/*
 +++++ Finds corresponding Token symbol of a string from input stream in O(1) time-complexity. +++++
 */

Trie<Token::Symbol> Lexer::mapToSymbol;


/*
 ++++++++++ Main C'tor ++++++++++++++
*/

Lexer::Lexer(const char *fileName)

	:
		inFile(fileName), stream(nullptr), tokensQ(new std::vector<Token>), 
		arrayD(nullptr), blockD(nullptr) , paramD(nullptr)
{

/*
 +++++ Load Trie with token symbols from TOKEN_LIST ++++++
 */

#define T(symbol, name) mapToSymbol.push(name, Token::symbol);
	
	TOKEN_LIST(T)

#undef T

};

std::vector<Token> &Lexer::operator ()(){

	while(inFile >> stream) generateTokensInQ();

	return *tokensQ;
};