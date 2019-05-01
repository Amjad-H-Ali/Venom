
// #include <iostream>
// // TOKEN_LIST takes in a Token Macro (T) and a string (S).
// // Each Macro has the same signature M(type, func(S)), 
// // where type is a unique symbol for the Token and func(S)
// // is some Boolean function that takes in a string as an 
// // argument.

// // T: Token Macro
// // S: String from input stream
// #define TOKEN_LIST(T, S) 								\
// 	T(STRING, isSTRING(S))								

// 	// T(IF, isIF(S))										\
// 	// T(EQ, isEQ(S))										\
// 	// T(BAR, isBAR(S))									\
// 	// T(EQEQ, isEQEQ(S))									\
// 	// T(ELSE, isELSE(S))									\
// 	// T(COMMA, isCOMMA(S))								\
// 	// T(OUTPUT, isOUTPUT(S))								\
// 	// T(BACKTICK, isBACKTICK(S))							\
// 	// T(IDENTIFIER, isIDENTIFIER(S))						\
// 	// T(SKINNY_ARROW, isSKINNYARROW(S))					


// // All Token Symbols
// #define T(symbol, name) symbol,
// 	// In this case, only the symbol is needed
// 	// and the second parameter is unused to
// 	// generate the List of Token Symbols.
// 	enum Symbol{TOKEN_LIST(T, S) NUM_OF_TOKENS};
// #undef T

// bool isSTRING(char *stream) {
// 	std::cout << stream << std::endl;
// 	if(stream[0] == '"') return true;
// 	return false;
// };

// class Token {

// public:

// 	Token(char *stream) {
// #define T(symbol, name) if(name) {setName((char *)#symbol); setType(symbol);}
// 	TOKEN_LIST(T, stream) 
// #undef T 
// 	};

// 	void setName(char *name) {
// 		this->name = name; 
// 	};
	

// 	void setType(Symbol type) {
// 		this->type = type;
// 	};

// 	char *name;
// 	Symbol type; 


// }; // Token


// int main(){

// 	Token token((char *)"\"");

// 	std::cout << token.name << std::endl;

// };



