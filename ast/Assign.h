#ifndef ASSIGN_H

#define ASSIGN_H


class Assign {

private:

	AST<ID> *lValuePtr;

	ast_t   *rValuePtr;

public:

	Assign()
	
		:lValuePtr(nullptr), rValuePtr(nullptr)
	{}

	void setValue(AST<ID> *lValuePtrParam, ast_t *rValuePtrParam) {

		lValuePtr = lValuePtrParam;

		rValuePtr = rValuePtrParam;
	}



}; // Assign



#endif