#pragma once 


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
	bool isSTRING(char *stream);		
	bool isOUTPUT(char *stream);	
	bool isBACKTICK(char *stream);	
	bool isIDENTIFIER(char *stream);
	bool isSKINNYARROW(char *stream);

}; // utility NameSpace




// TOKEN_LIST takes in a Token Macro (T).
// Each Macro has the same signature M(type, name), 
// where type is a unique symbol for the Token and name
// is a string containing the Token.

// T: Token Macro
#define TOKEN_LIST(T)							    \
	T(IF, "if")										\
	T(EQ, "=")										\
	T(BAR, "|")										\
	T(EQEQ, "==")									\
	T(ELSE, "else")									\
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
// 	T(STRING, utility::isSTRING(S))								\
// 	T(OUTPUT, utility::isOUTPUT(S))								\
// 	T(BACKTICK, utility::isBACKTICK(S))							\
// 	T(IDENTIFIER, utility::isIDENTIFIER(S))						\
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
	Token(char *stream) 
		:name(nullptr), type(), next(nullptr) 
	{

#define T(symbol, name) if(utility::isMatch(stream, (char *)name)) {setType(symbol); setName(stream);}
		TOKEN_LIST(T)
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


} // token NameSpace







