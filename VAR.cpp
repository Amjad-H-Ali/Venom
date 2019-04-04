#include "VAR.h"
#include <iostream>

using namespace std;



VAR::VAR(char *name):Token(VARIABLE) {
	this->set_name_len(name);
	this->set_name(name);
};
VAR::~VAR() {
	delete this->name;
};
char *VAR::get_value() const {
	return this->name;
};
void VAR::set_name(char *name) {
	this->name = new char[this->len+1];
	for(int i = 0; i < len; i ++)
		this->name[i] = name[i];
	this->name[this->len] = '\0';
};
int	VAR::get_len() const {
	return this->len;
};
void VAR::set_name_len(char *name) {
	int count = 0;
	while(name[count] != '\0')
		count ++;
	this->len = count;
};
Token *VAR::get_tok_value() const {
	return this->value;
};
void VAR::set_tok_value(Token *tok_ptr) {
	this->value = tok_ptr;
};
Token *VAR::next() {
	
	
	return this->Next;

};
void VAR::set_next(Token *tok_ptr){
	this->Next = tok_ptr;
};



