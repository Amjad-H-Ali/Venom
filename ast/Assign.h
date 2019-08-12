#ifndef ASSIGN_H

#define ASSIGN_H

#include "ast_t.h"


class Assign {

private:

	ast_t *lValue;

	ast_t *rValue;

public:

	Assign(ast_t&& lValueParam, ast_t&& rValueParam);	


	~Assign();

}; // Assign

#endif