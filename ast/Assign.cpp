#include "Assign.h"
#include "AST.h"

/*
 +++++ MAIN C'TOR +++++
 */
Assign::Assign(ast_t&& lValueParam, ast_t&& rValueParam)

	:lValue(new ast_t(std::move(lValueParam))), rValue(new ast_t(std::move(rValueParam)))
{}

/*
 +++++ Accessors +++++
 */
const ast_t& Assign::getLeftOperand() const {
	return *lValue;
}

const ast_t& Assign::getRightOperand() const {
	return *rValue;
}

/*
 +++++ RULE OF FIVE +++++
 */


/* 1
 +++++ COPY C'TOR +++++
 */

// Assign::Assign(const Assign& assignObj)

// 	:lValue(new ast_t(*assignObj.lValue)), rValue(new ast_t(*assignObj.rValue))
// {}



/* 2
 +++++ MOVE C'TOR +++++
 */

Assign::Assign(Assign&& assignObj)
	:lValue(assignObj.lValue), rValue(assignObj.rValue)
{

	assignObj.lValue = nullptr;

	assignObj.rValue = nullptr;
}

/* 3
 +++++ COPY ASSIGN +++++
 */

// Assign& Assign::operator=(const Assign& assignObj) {

// 	lValue = new ast_t(*assignObj.lValue);

// 	rValue = new ast_t(*assignObj.rValue);

// 	return *this;
// };

/* 4
 +++++ MOVE ASSIGN +++++
 */

Assign& Assign::operator=(Assign&& assignObj) {

	lValue = assignObj.lValue;

	rValue = assignObj.rValue;

	assignObj.lValue = nullptr;

	assignObj.rValue = nullptr;

	return *this;

}

/* 5
 +++++ DESTRUCTOR +++++
 */

Assign::~Assign() {

	if(lValue) delete lValue;

	if(rValue) delete rValue;

	lValue = nullptr;

	rValue = nullptr;
}
