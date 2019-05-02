#pragma once 


namespace Token {

namespace Utility {

	// Checks if two strings match.
	bool isMatch(char *s1, char *s2);

	// Utiltiy Functions To Help Determine Type of Tokens
	bool isIF(char *stream);				
	bool isEQ(char *stream);				
	bool isBAR(char *stream);			
	bool isEQEQ(char *stream);			
	bool isELSE(char *stream);			
	bool isCOMMA(char *stream);		
	bool isSTRING(char *stream);		
	bool isOUTPUT(char *stream);	
	bool isBACKTICK(char *stream);	
	bool isIDENTIFIER(char *stream);
	bool isSKINNYARROW(char *stream);

} // Utility NameSpace




// TOKEN_LIST takes in a Token Macro (T) and a string (S).
// Each Macro has the same signature M(type, func(S)), 
// where type is a unique symbol for the Token and func(S)
// is some Boolean function that takes in a string as an 
// argument.

// T: Token Macro
// S: String from input stream
#define TOKEN_LIST(T, S)								 		\
	T(IF, Utility::isIF(S))										\
	T(EQ, Utility::isEQ(S))										\
	T(BAR, Utility::isBAR(S))									\
	T(EQEQ, Utility::isEQEQ(S))									\
	T(ELSE, Utility::isELSE(S))									\
	T(COMMA, Utility::isCOMMA(S))								\
	T(STRING, Utility::isSTRING(S))								\
	T(OUTPUT, Utility::isOUTPUT(S))								\
	T(BACKTICK, Utility::isBACKTICK(S))							\
	T(IDENTIFIER, Utility::isIDENTIFIER(S))						\
	T(SKINNY_ARROW, Utility::isSKINNYARROW(S))					


// All Token Symbols
#define T(symbol, name) symbol,
	// In this case, only the symbol is needed
	// and the second parameter is unused to
	// generate the List of Token Symbols.
	enum Symbol{TOKEN_LIST(T, S) NUM_OF_TOKENS};
#undef T

class Token {

public:

	// Main Constructor
	Token(char *stream) 
		:name(nullptr), type(), next(nullptr) 
	{
#define T(symbol, name) if(name) {setName(stream); setType(symbol);} // TODO: ELSE DELETE STREAM & THROW EXCEPTION
	TOKEN_LIST(T, stream)
#undef T 
	};

	// Destructor
	~Token();

	// Methods
	void setName(char *name);

	void setType(Symbol type);

	void setNext(Token *tokenPtr);
	
	char *getName() const;

	Symbol getType() const;

	Token *getNext() const;

	// Data
private:
	char *name;
	Symbol type; 
	Token *next;


}; // Token


} // Token NameSpace







