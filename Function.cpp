#include "Function.h"

Function::Function(char *name, Token *parameters, Token *block, Type type):Identifier(name, type) {
	set_parameters(parameters);
	set_block(block);
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
Token *Function::get_block() const {
	return this->block;
};
void Function::set_block(Token *tok_ptr) {
	this->block = tok_ptr;
};