#include "AST_Node.h"


AST_Node::AST_Node(ast::AST_SYMBOL type) 
	:type(type)
{};


// Overload comparison operator to compare unique symbols 
bool AST_Node::operator==(ast::AST_SYMBOL type) const {
	return (this->type == type);
};

// Setters

// void AST_Node::setValue(ast::AST_SYMBOL type) {
// 	this->type = type;
// };

// Accessors

ast::AST_SYMBOL AST_Node::getType() const {
	return this->type;
};


char *AST_Node::getTypeName() const {

#define N(symbol) if (ast::symbol == this->type)return (char *)#symbol;
		AST_LIST(N)
#undef N

	else return nullptr;

};




