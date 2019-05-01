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
	T(SKINNYARROW, isSKINNYARROW(S))					\


	






