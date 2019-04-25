#pragma once
#include "Token.h"
#include "Identifier.h"
#include "Function.h"

// using namespace std;

namespace Lexer {
	struct Tokens {
		Token *token_head;
		Tokens *next;
	};
	void lexer(char *file_name);
	Token *get_statements(char &c, std::ifstream &in);
	char *get_string(char &c, std::ifstream &in);
	char *get_identifier(char &c, std::ifstream &in);
	char *get_operator(char &c, std::ifstream &in);
	Token *get_array_values(char &c, std::ifstream &in);
	Token *get_parameters(char &c, std::ifstream &in);
	Token *get_block(char &c, std::ifstream &in);
	Type which_identifier(char *identifier_ptr, char &c, std::ifstream &in, bool in_array=false);
	Type which_operator(char *c);
	int length_of_type(char &c, std::ifstream &in, bool(*green_light)(const char &));
	bool names_match(char *s1, char *s2);
	bool is_operator(const char &c);
	bool is_AtoZ(const char &c);
	bool not_quotes(const char &c);
	char multi_peek(std::ifstream &in, int places);
}
