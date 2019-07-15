#include <iostream>
#include <fstream>
#include "lexer.h"
#include "Token.h"
#include "ArrayDimension.h"
#include "BlockDimension.h"
#include "ParamDimension.h"
#include "utility.h"


class Lexer {

private:

	std::ifstream inFile;

	std::string stream;

	/*
		* Pointer to new Token object
		* that may be Instantiated soon.
	*/
	Token *newTokenPtr;


	Queue<Token> *tokensQ;

	/* 
		*
		* Gets the index of the string of where it no longer can be 
		* part of a potential identifier. 
		* Params: string containing data to tokenize and the start position
		* to read the string (defualt to beginning).
		*
    */
	std::string::size_type getIdentifierBreakPoint(const std::string &data, std::string::size_type start = 0) {
    	
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
		for(decltype(start) len = data.size(); (start < len) && 
			((data[start] >= 'a' && data[start] <= 'z') || 
			(data[start] >= 'A' && data[start] <= 'Z') ||
			(data[start] == '_') || ((start > beginning) && 
			(data[start] >= '0') && (data[start] <= '9'))); ++start);
   

    	return start;
	}


	void generateTokensInQ(std::string::size_type start = 0, std::string::size_type end = 0) {

		if(end == 0) end = stream.size();

	    if(start >= end) return;

	    /*
			*
			* Check if stream is the corresponding string value to any of the Token
			* symbols held in the Trie (Token::mapToSymbol). This can be a keyword,
			* paranthesis, comma, bracket, etc.
			*
	    */
	    if(Token::Symbol *sym = Token::mapToSymbol->map(data, start, end))
	        tokensQ.enqueue(*sym);
	    
	    /*
			*
			* If stream does not match any of the Token symbols, then it could be any of the following:
			*    * It's holding more than one value, meaning it contains values that were not spaced out (ie. "if(" ).
			*    * It's an identifier.
			* 	 * Otherwise, It's an error.
			*
	    */
	    else {
	    	/*
	    		*
	    		* Reccursively single out keywords, identifiers, operators, etc that are 
	    		* mashed together in the stream and Tokenize.
	    		*
	        */
	        decltype(start) aToZbreak = getIdentifierBreakPoint(data, start),
	                         symBreak = Token::mapToSymbol->getBreakPoint(data, start);
	    

	        if( (symBreak > 0) && (symBreak >= aToZbreak) && (sym = Token::mapToSymbol->map(data, start, symBreak)) ) {

	        	tokensQ.enqueue(*sym); 

	            start = symBreak;
	        }
	        
	        else {

	        	tokensQ.enqueue(stream.substr(start, aToZbreak), Token::IDENTIFIER); 

	            start = aToZbreak;
	        }

	        generateTokensInQ(start, end);
	    }
	    
	}

public:

	Lexer(const char *fileName)

		:inFile(fileName), newTokenPtr(nullptr)
	{};

	Queue<Token> *Tokenize() {

		tokensQ = new Queue<Token>;

		inFile >> std::noskipws;

		/*	
			********************* EOF but block remains open
			********************* because no more new lines.
		*/
		while(inFile >> stream || *blockD > 0) {

			/*
				*
				* When EOF and block still open, manually create 
				* new lines (Token::NEWLINE) to mark end. 
				*
			*/
			if(inFile.eof()) newTokenPtr = new Token(Token::NEWLINE);


			/*
				* 
				* Single Character Token (ie. BAR, RBRACKET, COMMA, etc.)
				*
			*/
			else if(isSingleCharSymbol()) {

				Token::Symbol *sym = Token::mapToSymbol->map(chompSingleCharSymbol());

				newTokenPtr = new Token(*sym);
			}

			/*
				*
				* AlphaNumeric(eg. Identifier, Keyword, etc.)
				*
			*/
			else if(isEligibleStartToAlphaNum()) {

				const char *someAlphaNum = chompAlphaNumeric();

				/*
					*
					* Check if value is a keyword (it would be in the Trie if it is).
					* If it's not a keyword, then it must be an Identifier. 
					***********************
					*********************** Returns nullptr or pointer to Token::Symbol.
				*/
				if(Token::Symbol *sym = Token::mapToSymbol->map(someAlphaNum))

					newTokenPtr = new Token(*sym);


				else
					/*
						*
						* Token Constructor for Identifier. 
						* Store Identifier name.
						*
					*/
					newTokenPtr = new Token(someAlphaNum, Symbol::IDENTIFIER);
			}

			/*
				* 
				* Potential Operator 
				*
			*/
			else if(isOperator(c)) 

				newTokenPtr = new token::Token(utils::chompOperator(c, in));





		} // while
	};

}; // Lexer


namespace utils = lexer::utility;


// Represents Dimensions of an array.
ArrayDimension *const arrayD = ArrayDimension::getInstance();

// Represents Dimension of a block.
BlockDimension *const blockD = BlockDimension::getInstance();

// Represents Dimension of a parameter list.
ParamDimension *const paramD = ParamDimension::getInstance();



// LEXER FUNCTIONS

// Tokenizes input file and adds to Linked List.
token::TokenNode *lexer::lexer(const char *fileName) {

	std::ifstream in(fileName);
	char c;

	// Head to Doubly-Linked-List of Token Nodes.
	token::TokenNode *headNode = nullptr;


	


	/*
		Read input file char by char
		Do not skip white space otherwise
		cannot differentiate between adjacent 
		AlphaNumeral characters belonging to 
		separate Tokens.
	*/
	in >> std::noskipws;
	while(in >> c || *blockD > 0) { 

		

		
		
		
		// String
		else if(utils::isQuote(c)) 
			newTokenPtr = new token::Token(utils::chompString(c, in), &utils::isQuote);
		// TAB
		else if(utils::isEscSeq(c))
			newTokenPtr = new token::Token(utils::chompSingleChar(c, in));
		
		else continue; // Probably throw an error here, but continue for spaces.



		token::TokenNode *newNode = new token::TokenNode;


		/*
			Insert new TokenNode in Doubly-Linked-List
			after setting its value to point to new Token Object.
		*/ 

		// Start ...

		newNode->tokenPtr = newTokenPtr;

		newNode->next = headNode;

		// Access prev property of neighbor node and point it to this newNode.
		if(headNode) newNode->next->prev = newNode; 
		headNode = newNode;

		// Finish.

		/*
			If Token Node belongs to open/exit of an array or block,
			record it in respective Dimension Object.
		*/
		if(utils::isDimensional(in, newNode)) lexer::insertDimension(newNode);	
		
	} // While

	std::cout << blockD->getD()<< std::endl;


	return headNode;


}; // Lexer

// Inserts start/end to block or array in 
// respective Object.
void lexer::insertDimension(token::TokenNode *tn) {

	if(*tn == token::LBRACKET) {
		std::cout << "OPEN to Array" << std::endl;
		arrayD->insertOpen(tn);
	}

	else if (*tn == token::SKINNY_ARROW) {
		std::cout << "OPEN to Func" << std::endl;
		blockD->insertOpen(tn);
	}
	else if(*paramD == 0  && *tn == token::BAR) {
		std::cout << "OPEN to PARAM" << std::endl;
		paramD->insertOpen(tn);
	}
	else if(*paramD > 0 && *tn == token::BAR) {
		std::cout << "Close to PARAM" << std::endl;
		paramD->insertClose(tn);
	}

	else if (*tn == token::RBRACKET) {
		std::cout << "Close to Array" << std::endl;
		arrayD->insertClose(tn);
	}
	else {
		std::cout << "Close to Func" << std::endl;
		blockD->insertClose(tn);
	}
	
};


// UTILITY FUNCTIONS

// Gets whole Potential String from beginning to end.
char *utils::chompString(char &c, INFILE in) {

	 
	// Either a Single Quote or Double Quote.
	char quote = c;


	// Function that will be passed into rangeToChomp.
	bool(*func)(const char) = (quote == '"' ? &isNotClosingDoubleQT : &isNotClosingSingleQT);

	// Skip Quote so rangeToChomp can continue
	in >> c;

	// Range to Chomp 								
	auto range = utils::rangeToChomp(c, in, func);


	char *potentialString = utils::makeC_String(in, range);

	// Skip closing quote.
	in >> c;

	return potentialString;
};


// Gets Potential Operator
char *utils::chompOperator(char &c, INFILE in) {

	// Range to Chomp
	auto range = utils::rangeToChomp(c, in, &isOperator);

	return utils::makeC_String(in, range);
}


// Gets whole AlphaNumeric from beginning to end.
char *utils::chompAlphaNumeric(char &c, INFILE in) {

	// Range to Chomp
	auto range = utils::rangeToChomp(c, in, &isAlphaNumeric);

	return utils::makeC_String(in, range);
};

// Chomp Single Token
char *utils::chompSingleChar(char &c, INFILE in) {
	// Range to Chomp
	// No need for rangeToChomp if Single Character Token

	// Set file pointer before Character to chomp
	// since read is not start inclusive.
	in.seekg(in.tellg()-(decltype(in.tellg()))1, in.beg);

	return utils::makeC_String(in, 1);
};


// Creates a C-String. Parameters are an ifstream object
// from which it will read in characters from current state
// of this file object, and the range of characters to read.
char *utils::makeC_String(INFILE in, std::streampos range) {

	// Make a C String.
	char *name = new char[range+(decltype(in.tellg()))1];

	// Read in to name.
	in.read(name, range);

	name[range] = '\0';


	return name;
};  


// Determines the length of stream to chomp based on the 
// Bool Function passed in as argument. Restores file pointer
// to original position when finished.
std::streampos utils::rangeToChomp(char &c, INFILE in, bool(*greenLight)(const char)) {

	decltype(in.tellg()) startPos = in.tellg(), offset = 0, endPos, range;

	while(greenLight(c) && !in.eof()) {

		offset+= (decltype(in.tellg()))1;
		in>>c;

	}

	endPos = startPos + offset;
	range = endPos - startPos;

	// Reset file pointer to original position.
	in.clear();
	in.seekg(startPos-(decltype(in.tellg()))1, in.beg);

	return range;
};


// Check if character is an eligible operator.
bool utils::isOperator(char c) {
	return (
		c == '=' || c == '+' || c == '-' || c == '*' ||
	    c == '/' || c == '%' || c == '>' || c == '<'
	);
};

// Checks if current charachter is a number
bool utils::isNumeric(char c) {
	return (c >= '0' && c <= '9');
}

// Checks if current character is a letter.
bool utils::isAtoZ(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
};

// Checks if character is Alphanumeric (A-Z, 0-9, or _)
bool utils::isAlphaNumeric(char c) {
	return (utils::isAtoZ(c) || utils::isNumeric(c) || c == '_');
};

// Checks if character is an eligible beggining for AlphaNumeric.
bool utils::isEligibleStartToAlphaNum(char c) {
	return (utils::isAtoZ(c) || c == '_');
};

// Checks if character is a Quote
bool utils::isQuote(char c) {
	return (c == '"' || c == '\'');
};

// Returns true if not a single Quote.
bool utils::isNotClosingSingleQT(char c) {
	return (c != '\'');
};
// Returns true if not a double Quote.
bool utils::isNotClosingDoubleQT(char c) {
	return (c != '"');
};
 
// Checks if one of the singly named Tokens (eg. `, |, (, ), etc.)
bool utils::isSinglyNamedToken(char c) {
	return (
			c == '`' || c == '|' || c == '[' ||
			c == '(' || c == ')' || c == ',' ||
			c == ']'
	);
};

// Checks if character is one of the relevant Escape Sequences.
bool utils::isEscSeq(char c) {
	return (c == '\t' || c == '\n'); // To Add, Soon.
};

/*
	Checks if Token Node is part of an array or block,
	which is Dimensional.
*/
bool utils::isDimensional(INFILE in, token::TokenNode *tn) {

	return (
		*tn == token::LBRACKET || *tn == token::RBRACKET ||
		*tn == token::SKINNY_ARROW || *tn == token::BAR  ||
		(*blockD > 0 && isClosingBlock(in, tn))
	);
};

// Checks if Token Node is last in block.
bool utils::isClosingBlock(INFILE in, token::TokenNode *tn) {
	return (
		(	// If NEWLINE is an exit to a block.
			*tn == token::NEWLINE &&
			!utils::rangeOnlyHas(in, blockD->getD(), '\t')
		) 
		/*
			Token Node Closes Block if it's last in file.
			Use of peekAhead instead of istream::peek because 
			peek does not skip spaces, peekAhead does.
		*/
		|| utils::peekAhead(in, 1) == EOF
	);
};

// Checks if range ahead contains only given character.
bool utils::rangeOnlyHas(INFILE in, int places, char c) {
	char container;
	// Remember start position
	auto startPos = in.tellg();

	in >> std::noskipws;

	for(int i = 0;i < places; i ++) {

		in >> container;

		if(in.eof()) return EOF;

		if(container == '\n' || container == ' ') {i--; continue;}

		std::cout << "RANGE" << std::endl;
		
		if(container != c) return false;
	}

	in.seekg(startPos);
	return true;
};

/*
	To Peek multiple characters Ahead.

	Params: ifstream object and Number 
	of places to Peek Ahead.

	Skips spaces.
*/
char utils::peekAhead(INFILE in, int places) {
	char result;
	char container; 

	// To remember starting position
	auto startPos = in.tellg();

	in >> std::noskipws;

	// Skip ahead and peek.
	for(int i = 0; i < places; i ++) {
		in >> container;

		if(in.eof()) return EOF;

		// To Skip Spaces ' ' 0x20, but not other ws.
		if(container == ' ') {i--; continue;}

		result = container;
	}

	// Return to start position
	in.seekg(startPos);

	return result;
};







