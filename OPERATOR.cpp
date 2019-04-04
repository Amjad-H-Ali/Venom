#include "OPERATOR.h"

OPERATOR::OPERATOR(char *value):Token(OPER) {
	this->set_len(value);
	this->set_value(value);
};
OPERATOR::~OPERATOR() {
	delete this->value;
};
char *OPERATOR::get_value() const {
	return this->value;
};
void OPERATOR::set_value(char *value) {
	this->value = new char[this->len+1];
	for(int i = 0; i < this->len; i ++)
		this->value[i] = value[i];
	this->value[this->len] = '\0';
};
int OPERATOR::get_len() const {
	return this->get_len();
};
void OPERATOR::set_len(char *value) {
	int count = 0;

	while(value[count] != '\0')
		count ++;
	this->len = count;
};
Token *OPERATOR::get_left() const {
	return this->left;
};
void OPERATOR::set_left(Token *tok_ptr) {
	this->left = tok_ptr;
};
Token *OPERATOR::get_right() const {
	return this->right;
};
void OPERATOR::set_right(Token *tok_ptr) {
	this->right = tok_ptr;
};

Token *OPERATOR::next() {
	
	
	return this->Next;

};
void OPERATOR::set_next(Token *tok_ptr){
	this->Next = tok_ptr;
};