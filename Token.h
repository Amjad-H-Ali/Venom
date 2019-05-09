#pragma once 
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

	// Utiltiy Functions To Help Determine Type of Tokens
	bool isIF(char *stream);				
	bool isEQ(char *stream);				
	bool isBAR(char *stream);			
	bool isEQEQ(char *stream);			
	bool isELSE(char *stream);			
	bool isCOMMA(char *stream);		
	bool isOUTPUT(char *stream);	
	bool isBACKTICK(char *stream);	
	bool isSKINNYARROW(char *stream);

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
	T(EQEQ, "==")									\
	T(ELSE, "else")									\
	T(ELIF, "elif")									\
	T(COMMA, ",")									\
	T(STRING, nullptr)								\
	T(OUTPUT, "output")								\
	T(BACKTICK, "`")								\
	T(IDENTIFIER, nullptr)						    \
	T(SKINNY_ARROW, "->")



// #define TOKEN_LIST(T, S)								 		\
// 	T(IF, utility::isIF(S))										\
// 	T(EQ, utility::isEQ(S))										\
// 	T(BAR, utility::isBAR(S))									\
// 	T(EQEQ, utility::isEQEQ(S))									\
// 	T(ELSE, utility::isELSE(S))									\
// 	T(COMMA, utility::isCOMMA(S))								\
// 	T(STRING, nullptr)								            \
// 	T(OUTPUT, utility::isOUTPUT(S))								\
// 	T(BACKTICK, utility::isBACKTICK(S))							\
// 	T(IDENTIFIER, nullptr)						                \
// 	T(SKINNY_ARROW, utility::isSKINNYARROW(S))					
					



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
		:next(nullptr), prev(nullptr)
	{	
		

		if(hint == &lexer::utility::isQuote) {setType(STRING); setName(stream); setTypeName((char *)"STRING");}

// #define T(symbol, name) else if(name) {setType(symbol); setName(stream);}
// 		TOKEN_LIST(T, stream)
// #undef T

#define T(symbol, name) else if(utility::isMatch(stream, (char *)name)) {setType(symbol); setName(stream); setTypeName((char *)#symbol);}
		TOKEN_LIST(T)
#undef T
		// If AlphaNum and not any keyword, must be Identifier.
		else if(hint == &lexer::utility::isEligibleStartToAlphaNum) {setType(IDENTIFIER); setName(stream); setTypeName((char *)"IDENTIFIER");}
		
		// Else Throw Exception
	};

	// Destructor
	~Token();

	// Methods
	void setName(char *name);

	void setType(Symbol type);

	void setNext(Token *tokenPtr);

	void setPrev(Token *tokenPtr);

	void setTypeName(char *typeName);
	
	char *getName() const;

	Symbol getType() const;

	Token *getNext() const;

	Token *getPrev() const;

	char *getTypeName() const;

	// Data
private:
	char *name;
	Symbol type; 
	Token *next;
	Token *prev;
	char *typeName;


}; // Token


}; // token NameSpace







