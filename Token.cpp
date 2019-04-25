#include "Token.h"

Token::Token(char *name, Type type) {
	this->set_type(type);
	this->set_name_len(name);
	this->set_name(name);
};
Token::~Token() {
	delete this->name;
};
void Token::set_type(Type type) {
	this->type = type;
};
Type Token::get_type() const {
	return this->type;
};
void Token::set_name(char *name) {
	this->name = name;
};
char *Token::get_name() const {
	return this->name;
};
void Token::set_name_len(char *name) {
	int count = 0;
	while(name[count] != '\0')
		count++;
	this->name_len = count;
};
int Token::get_name_len() const {
	return this->name_len;
};
void Token::set_next(Token *tok_ptr) {
	this->next = tok_ptr;
};
Token *Token::get_next() const {
	return this->next;
};

Token *Token::get_value() const {return 0;};
void Token::set_value(Token *tok_ptr) {};
Token *Token::get_parameters() const {return 0;};
Token *Token::get_block() const {return 0;};
Token *Token::get_arguments() const {return 0;};