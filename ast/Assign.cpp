#include "Assign.h"
#include "AST.h"


Assign::Assign(ast_t&& lValueParam, ast_t&& rValueParam)

	:lValue(new ast_t(std::move(lValueParam))), rValue(new ast_t(std::move(rValueParam)))
{}


Assign::~Assign() {

	delete lValue;

	delete rValue;
}
