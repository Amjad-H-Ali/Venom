#include "Add.h"
#include "AST.h"

Add::Add(ast_t&& lOperandParam, ast_t&& rOperandParam)

	:lOperand(new ast_t(std::move(lOperandParam))), rOperand(new ast_t(std::move(rOperandParam)))

{}

Add::~Add() {

	delete lOperand;

	delete rOperand;
}