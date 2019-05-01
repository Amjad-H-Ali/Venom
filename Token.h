#pragma once 

// TOKEN_LIST takes in a Token Macro (T) and a string (S).
// Each Macro has the same signature M(type, func(S)), 
// where type is a unique symbol for the Token and func(S)
// is some Boolean function that takes in a string as an 
// argument.

// T: Token Macro
// S: String from input stream
#define TOKEN_LIST(T, S)								\
	T(IF, isIF(S))										\
	T(EQ, isEQ(S))										\
	T(BAR, isBAR(S))									\
	T(EQEQ, isEQEQ(S))									\
	T(ELSE, isELSE(S))									\
	T(COMMA, isCOMMA(S))								\
	T(STRING, isSTRING(S))								\
	T(OUTPUT, isOUTPUT(S))								\
	T(BACKTICK, isBACKTICK(S))							\
	T(IDENTIFIER, isIDENTIFIER(S))						\
	T(SKINNY_ARROW, isSKINNYARROW(S))					


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
		:name(), type(), next() 
	{
#define T(symbol, name) if(name) {setName(stream); setType(symbol);} // TODO: ELSE THROW EXCEPTION
	TOKEN_LIST(T, stream)
#undef T 
	};



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


} // Token






