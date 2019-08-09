#ifndef ASSIGN_H

#define ASSIGN_H


class Assign {

private:

	AST<ID> lValue;

	ast_t   rValue;

public:

	Assign(AST<ID>&& lValueParam, ast_t&& rValueParam)

		:lValue(std::move(lValueParam)), rValue(std::move(rValueParam))
	{}

	



}; // Assign



#endif