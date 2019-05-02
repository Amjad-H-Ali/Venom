#pragma once
#include "Token.h"
#include "Identifier.h"
#include "Function.h"
#include "FunctionCall.h"



namespace Lexer {

namespace Utility	{
		


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
		int rangeToChomp(char &c, ifstream &in, bool(*greenLight)(const char));

		bool is_operator(const char &c);
		bool isAtoZ(char c);
		bool isNumeric(char c);
		bool isAlphaNumeric(char c);
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
