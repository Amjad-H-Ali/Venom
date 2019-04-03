#pragma once
#include "Token.h"

class STRING: public Token {
private:
	int  len;
	char *value;
public:
	STRING(char *str, int len);
	~STRING();
	int get_len() const;
	void set_len(int len);
	char *get_value() const;
	void set_value(char *str);
};