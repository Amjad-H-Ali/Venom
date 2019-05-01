#pragma once
#include "Token.h"
#include "Identifier.h"
#include "Function.h"
#include "FunctionCall.h"



namespace Lexer {

namespace Utility	{
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





		void lexer(char *file_name);
		Token *get_statements(char &c, std::ifstream &in);
		char *get_string(char &c, std::ifstream &in);
		char *get_identifier(char &c, std::ifstream &in);
		char *get_operator(char &c, std::ifstream &in);
		Token *get_array_values(char &c, std::ifstream &in);
		Token *get_parameters(char &c, std::ifstream &in);
		Token *get_block(char &c, std::ifstream &in);
		Token *get_arguments(char &c, std::ifstream &in);
		Type which_identifier(char *identifier_ptr, char &c, std::ifstream &in, bool in_array=false);
		Type which_operator(char *c);
		int length_of_type(char &c, std::ifstream &in, bool(*green_light)(const char &));

		// Checks if two strings match.
		bool isMatch(char *s1, char *s2);
		bool is_operator(const char &c);
		bool is_AtoZ(const char &c);
		bool not_quotes(const char &c);

		// To Peek multiple characters Ahead
		// Params: iStream object and Amount 
		// of places to Peek Ahead.
		char peekAhead(std::ifstream &in, int places);



}; // Utility Namespace

	struct Tokens {
		Token *token_head;
		Tokens *next;
	}; // Tokens Struct
	
}; // Lexer Namespace
