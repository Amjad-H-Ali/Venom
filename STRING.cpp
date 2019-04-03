#include "STRING.h"

STRING::STRING(char *str, int len):Token(STR) {
	this->set_len(len);
	this->set_value(str);
};
STRING::~STRING() {
	delete this->value;
};
int STRING::get_len() const {
	return this->len;
};
void STRING::set_len(int len) {
	this->len = len;
};
char *STRING::get_value() const {

	return this->value;
};
void STRING::set_value(char *str) {
	this->value = new char[this->len + 1];
	for(int i = 0; i < this->len; i ++) 
		this->value[i] = str[i];
	this->value[this->len + 1] = '\0';
};	