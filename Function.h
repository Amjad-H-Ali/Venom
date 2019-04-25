#pragma once
#include "Token.h"

class Function:public Token {
private:
	Token *parameters;
	Token *block;
	
public:
	Function(char *name, Token *parameters, Token *block, Type type);
	~Function();
	Token *get_parameters() const;
	void set_parameters(Token *tok_ptr);
	Token *get_block() const;
	void set_block(Token *tok_ptr);
};