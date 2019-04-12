#pragma once
#include "Token.h"


class Identifier: public Token {
private:
	Token *value;
public:
	Identifier(char *name, Type type);
	~Identifier();
	Token  *get_value() const;
	void  set_value(Token *tok_ptr);
};

