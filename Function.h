#pragma once
#include "Identifier.h"

class Function:public Identifier {
private:
	Token *parameters;
	Token *opening;
	Token *closing;
public:
	Function(char *name, Token *parameters, Token *opening, Token *closing, Type type);
	Token *get_parameters() const;
	void set_parameters(Token *tok_ptr);
	Token *get_opening() const;
	void set_opening(Token *tok_ptr);
	Token *get_closing() const;
	void set_closing(Token *tok_ptr);
};