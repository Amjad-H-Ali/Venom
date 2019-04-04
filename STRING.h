#pragma once
#include "Token.h"

class STRING: public Token {
private:
	int  len;
	char *value;
public:
	STRING(char *str);
	~STRING();
	int get_len() const;
	void set_len(char *str);
	char *get_value() const;
	void set_value(char *str);
	Token *next();
	void set_next(Token *tok_ptr);
};