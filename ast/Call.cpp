#include "Call.h"
#include "AST.h"

/*
 +++++ MAIN C'TOR +++++
 */
Call::Call(ast_t&& lOperandParam, const std::vector<ast_t> *argListParam)

	:lOperand(new ast_t(std::move(lOperandParam))), argList(argListParam)
{}

/*
 +++++ Accessors +++++
 */
const ast_t& Call::getLeftOperand() const {
	return *lOperand;
}

const std::vector<ast_t>& Call::getArgList() const {
	return *argList;
}

/*
 +++++ RULE OF FIVE +++++
 */


/* 1
 +++++ COPY C'TOR +++++
 */

// Call::Call(const Call& callObject)

// 	:lOperand(new ast_t(*callObject.lOperand)), argList(new std::vector<ast_t> (*callObject.argList))
// {}



/* 2
 +++++ MOVE C'TOR +++++
 */

Call::Call(Call&& callObject)
	:lOperand(callObject.lOperand), argList(callObject.argList)
{

	callObject.lOperand = nullptr;

	callObject.argList = nullptr;
}

/* 3
 +++++ COPY C'TOR +++++
 */

// Call& Call::operator=(const Call& callObject) {

// 	lOperand = new ast_t(*callObject.lOperand);

// 	argList = new std::vector<ast_t>(*callObject.argList);

// 	return *this;
// };

/* 4
 +++++ MOVE Call +++++
 */

Call& Call::operator=(Call&& callObject) {

	lOperand = callObject.lOperand;

	argList = callObject.argList;

	callObject.lOperand = nullptr;

	callObject.argList = nullptr;

	return *this;

}

/* 5
 +++++ DESTRUCTOR +++++
 */

Call::~Call() {

	if(lOperand) delete lOperand;

	if(argList) delete argList;

	lOperand = nullptr;

	argList = nullptr;
}
