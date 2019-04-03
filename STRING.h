
#include "Token.h"

#pragma once


class STRING: public Token {
private:
	int  len;
	char *value;
public:
	STRING(char *str, int len);
	int get_len() const;
	void set_len(int len);
	char *get_value() const;
	void set_value(char *str);
};