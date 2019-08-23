#include "Write.h"
#include "AST.h"

/*
 +++++ MAIN C'TOR +++++
 */

Write::Write(ast_t&& valueParam)

	:value(new ast_t(std::move(valueParam)))
{}

/*
 +++++ Accessors +++++
 */
const ast_t& Write::getValue() const {
	return *value;
}


/*
 +++++ RULE OF FIVE +++++
 */

/* 1
 +++++ COPY C'TOR +++++
 */

// Write::Write(const Write& writeObj)

// 	:value(new ast_t(*writeObj.value))
// {}

/* 2
 +++++ MOVE C'TOR +++++
 */

Write::Write(Write&& writeObj)
	:value(writeObj.value)
{

	writeObj.value = nullptr;

}

/* 3
 +++++ COPY ASSIGN +++++
 */

// Write& Write::operator=(const Write& writeObj) {

// 	value = new ast_t(*writeObj.value);
//
// 	return *this;
// };

/* 4
 +++++ MOVE ASSIGN +++++
 */

Write& Write::operator=(Write&& writeObj) {

	value = writeObj.value;

	writeObj.value = nullptr;

	return *this;

}

/* 5
 +++++ DESTRUCTOR +++++
 */

Write::~Write() {

	if(value) delete value;

	value = nullptr;

}