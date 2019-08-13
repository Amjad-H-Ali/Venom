#include "Add.h"
#include "AST.h"

/*
 +++++ MAIN C'TOR +++++
 */

Add::Add(ast_t&& lOperandParam, ast_t&& rOperandParam)

	:lOperand(new ast_t(std::move(lOperandParam))), rOperand(new ast_t(std::move(rOperandParam)))
{}


/*
 +++++ RULE OF FIVE +++++
 */

/* 1
 +++++ COPY C'TOR +++++
 */

Add(const Add& addObj) {

	lOperand = new lOperand(addObj.lOperand);

	rOperand = new rOperand(addObj.rOperand);
}

/* 2
 +++++ MOVE C'TOR +++++
 */

Add(Add&& addObj)
	:lOperand(addObj.lOperand), rOperand(addObj.rOperand);
{

	addObj.lOperand = nullptr;

	addObj.rOperand = nullptr;
}

/* 3
 +++++ COPY ASSIGN +++++
 */

Add& operator=(const Add& addObj) {

	lOperand = new lOperand(addObj.lOperand);

	rOperand = new rOperand(addObj.rOperand);

	return *this;
};

/* 4
 +++++ MOVE ASSIGN +++++
 */

Add& operator=(Add&& addObj) {

	lOperand = addObj.lOperand;

	rOperand = addObj.rOperand;

	addObj.lOperand = nullptr;

	addObj.rOperand = nullptr;

	return *this;

}

/* 5
 +++++ DESTRUCTOR +++++
 */

Add::~Add() {

	if(lOperand) delete lOperand;

	if(rOperand) delete rOperand;

	lOperand = nullptr;

	rOperand = nullptr;

}