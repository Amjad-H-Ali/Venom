#pragma once
#include "Token.h"

class OPERATOR:public Token {
private:
	char  *value;
	Token *left, *right;
	int   len;
public:
	OPERATOR(char *value);
	~OPERATOR();
	char *get_value() const;
	void set_value(char *value);
	int get_len() const;
	void set_len(char *value);
	Token *get_left() const;
	void set_left(Token *tok_ptr);
	Token *get_right() const;
	void set_right(Token *tok_ptr);
};