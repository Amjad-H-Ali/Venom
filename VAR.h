#pragma once
#include "Token.h"


class VAR: public Token {
private:
	int   len;
	char  *name;
	Token *value;
public:
	VAR(char *name, int len);
	~VAR();
	char  *get_value() const;
	void  set_name(char *name);
	int   get_len() const;
	void  set_name_len(int len);
	Token *get_tok_value() const;
	void  set_tok_value(Token *tok_ptr);

};

