#include "Identifier.h"


Identifier::Identifier(char *name, Type type):Token(name, type) {

};
Identifier::~Identifier() {
	delete this->name;
};
Token *Identifier::get_value() const {
	return this->value;
};
void Identifier::set_value(Token *tok_ptr) {
	this->value = tok_ptr;
};




