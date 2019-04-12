#pragma once
#include "Token.h"
// #include "Definitions.h"



class Identifier: public Token {
private:
	// int   len;
	// char  *name;
	Token *value;
public:
	Identifier(char *name, Type type);
	~Identifier();
	Token  *get_value() const;
	void  set_value(Token *tok_ptr);
	// void  set_name(char *name);
	// int   get_len() const;
	// void  set_name_len(char *name);
	// Token *get_value() const;
	// Token *next();
	// void set_next(Token *tok_ptr);

};

