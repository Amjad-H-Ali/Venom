#include "Assign.h"
#include "AST.h"

/*
 +++++ MAIN C'TOR +++++
 */
Assign::Assign(ast_t&& lValueParam, ast_t&& rValueParam)

	:lValue(new ast_t(std::move(lValueParam))), rValue(new ast_t(std::move(rValueParam)))
{}


/*
 +++++ RULE OF FIVE +++++
 */



/* 1
 +++++ COPY C'TOR +++++
 */

Assign(const Assign& assignObj) {

	lValue = new lValue(assignObj.lValue);

	rValue = new rValue(assignObj.rValue);
}

/* 2
 +++++ MOVE C'TOR +++++
 */

Assign(Assign&& assignObj)
	:lValue(assignObj.lValue), rValue(assignObj.rValue);
{

	assignObj.lValue = nullptr;

	assignObj.rValue = nullptr;
}

/* 3
 +++++ COPY ASSIGN +++++
 */

Assign& operator=(const Assign& assignObj) {

	lValue = new lValue(assignObj.lValue);

	rValue = new rValue(assignObj.rValue);

	return *this;
};

/* 4
 +++++ MOVE ASSIGN +++++
 */

Assign& operator=(Assign&& assignObj) {

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
