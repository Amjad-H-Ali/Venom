#ifndef TOKEN_H

#define TOKEN_H

#include "lexer.h"


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




// TOKEN_LIST takes in a Token Macro (T).
// Each Macro has the same signature M(type, name), 
// where type is a unique symbol for the Token and name
// is a string containing the Token.

// T: Token Macro
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
	T(BACKTICK, "`")								\
	T(IDENTIFIER, nullptr)						    
								




// All Token Symbols
#define T(symbol, name) symbol,
	// In this case, only the symbol is needed
	// and the second parameter is unused to
	// generate the List of Token Symbols.
	enum Symbol{TOKEN_LIST(T) NUM_OF_TOKENS};
#undef T


class Token {

public:

	

	// Main Constructor
	Token(char *stream, bool(*hint)(char)=nullptr) 
	{	
		

		if(hint == &lexer::utility::isQuote) {setType(STRING); setName(stream); setTypeName((char *)"STRING");}



#define T(symbol, name) else if(utility::isMatch(stream, (char *)name)) {setType(symbol); setName(stream); setTypeName((char *)#symbol);}
		TOKEN_LIST(T)
#undef T
		// If AlphaNum and not any keyword, must be Identifier.
		else if(hint == &lexer::utility::isEligibleStartToAlphaNum) {setType(IDENTIFIER); setName(stream); setTypeName((char *)"IDENTIFIER");}
		
		// Else Throw Exception
	};

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
	char *name, *typeName;
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





