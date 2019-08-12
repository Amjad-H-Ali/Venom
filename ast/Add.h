#ifndef ADD_H

#define ADD_H


#include "ast_t.h"



class Add {

private:

	ast_t *lOperand;

	ast_t *rOperand;


public:


	Add(ast_t&& lOperandParam, ast_t&& rOperandParam);

	~Add();



}; // Add

#endif