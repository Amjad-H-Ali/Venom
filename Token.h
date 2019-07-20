#ifndef TOKEN_H

#define TOKEN_H

#include "lexer.h"
#include <vector>



// Forward Declaration of lexer::utility functions.
namespace lexer { namespace utility {
	bool isQuote(char c);
	bool isEligibleStartToAlphaNum(char c);

}}; // End of forward Declaration of lexer::utility functions.

namespace token {

namespace utility {

	// Checks if two strings match.
	bool isMatch(char *s1, char *s2);

}; // utility NameSpace



/*
	* TOKEN_LIST takes in a Token Macro (T).
	* Each Macro has the same signature M(type, name), 
	* where type is a unique symbol for the Token and name
	* is a string containing the Token.

	* T: Token Macro
*/
#define TOKEN_LIST(T)							    \
	T(IS, "is")									    \
	T(IF, "if")										\
	T(EQ, "=")										\
	T(BAR, "|")										\
	T(TAB, "\t")									\
	T(EQEQ, "==")									\
	T(ELSE, "else")									\
	T(ELIF, "elif")									\
	T(COMMA, ",")									\
	T(ARROW, "->")									\
	T(STRING, nullptr)								\
	T(OUTPUT, "output")								\
	T(NEWLINE, "\n")								\
	T(LBRACKET, "[")								\
	T(RBRACKET, "]")								\
	T(LHANDLE, ":|")								\
	T(RHANDLE, "|:")								\
	T(BACKTICK, "`")								\
	T(IDENTIFIER, nullptr)						    
								







class Token {

public:


	/*
		*
		* All Token Symbols
		*
	*/
#define T(symbol, name) symbol,
	/* 
		* In this case, only the symbol is needed
		* and the second parameter is unused to
		* generate the List of Token Symbols.
	*/
	enum Symbol{TOKEN_LIST(T) NUM_OF_TOKENS};

#undef T


	/*
		*
		* Used to map strings (C-Style) to their corresponding
		* Symbol in O(n) time complexity.
		*
	*/
	static Trie<Symbol *> *mapToSymbol;

	/*
		*
		* All Token symbols in string form for logging.
		*
	*/
	static std::vector<std::string> typeName;

	

	/*
		----------------
		  Constructors
		----------------
	*/

	/*
		*
		* IDENTIFIER and STRING Constructor.
		*
	*/
	Token(const std::string &stream, Symbol type) {

		value = stream;

		type = type;
	}

	/*
		*
		* Constructor for Everything else like keywords, operators, etc,
		*
	*/
	Token(Symbol type) 
		:value(nullptr)
	{
		type = type;
	}




	// Destructor
	~Token();

	// Overload == operator to compare symbol types.
	bool operator==(Symbol type) const;

	// Methods
	void setName(char *name=nullptr);

	void setType(Symbol type);

	void setTypeName(char *typeName);
	
	char *getName() const;

	Symbol getType() const;

	char *getTypeName() const;

	// Data
private:
	/*
		*
		* This data member is set to nullptr unless type is a STRING or IDENTIFIER.
		*
	*/
	std::string value;


	Symbol type; 

}; // Token


// Token Node In Linked-List
struct TokenNode {

	token::Token *tokenPtr;

	// If this node is a "closing" or "opening" to a BLOCK or LIST,
	// then it has a matching pair. Every other nodes' is set to nullptr.
	token::TokenNode *next, *prev, *matchingPair;

	// Indicates that this node is an end to a BLOCK or LIST.
	bool closing;

	TokenNode()
		:
			tokenPtr(nullptr), next(nullptr), prev(nullptr), 
			matchingPair(nullptr), closing(false)
	{};

	~TokenNode() {
		if(this->tokenPtr != nullptr) {
			delete this->tokenPtr;
			this->tokenPtr = nullptr;
		}
	};

	// Overload Operators to compare symbols of objects.
	bool operator==(token::Symbol type) const {
		// Call overloaded operator of Token Object.
		return (*(this->tokenPtr) == type);
	}

	bool operator!=(token::Symbol type) const {
		return (this->tokenPtr->getType() != type);
	}

}; // TokenNode Struct


}; // token NameSpace

#endif





