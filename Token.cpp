#include "Token.h"


Token::Token(Type type) {
	this->set_type(type);
};

Type Token::get_type() const {
	return this->type;
};
void Token::set_type(Type type) {
	this->type = type;
};