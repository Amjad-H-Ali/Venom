#include "Function.h"

Function::Function(char *name, Token *parameters, Token *opening, Token *closing, Type type):Identifier(name, type) {
	set_parameters(parameters);
	set_opening(opening);
	set_closing(closing);
};
Function::~Function() {
	delete this->name;
};
Token *Function::get_parameters() const {
	return this->parameters;
};
void Function::set_parameters(Token *tok_ptr) {
	this->parameters = tok_ptr;
};
Token *Function::get_opening() const {
	return this->opening;
};
void Function::set_opening(Token *tok_ptr) {
	this->opening = tok_ptr;
};
Token *Function::get_closing() const {
	return this->closing;
};
void Function::set_closing(Token *tok_ptr) {
	this->closing = tok_ptr;
};
