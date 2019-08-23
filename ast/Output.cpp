#include "Output.h"
#include "AST.h"

/*
 +++++ MAIN C'TOR +++++
 */

Output::Output(ast_t&& valueParam)

	:value(new ast_t(std::move(valueParam)))
{}

/*
 +++++ Accessors +++++
 */
const ast_t& Output::getValue() const {
	return *value;
}


/*
 +++++ RULE OF FIVE +++++
 */

/* 1
 +++++ COPY C'TOR +++++
 */

// Output::Output(const Output& outputObj)

// 	:value(new ast_t(*outputObj.value))
// {}

/* 2
 +++++ MOVE C'TOR +++++
 */

Output::Output(Output&& outputObj)
	:value(outputObj.value)
{

	outputObj.value = nullptr;

}

/* 3
 +++++ COPY ASSIGN +++++
 */

// Output& Output::operator=(const Output& outputObj) {

// 	value = new ast_t(*outputObj.value);
//
// 	return *this;
// };

/* 4
 +++++ MOVE ASSIGN +++++
 */

Output& Output::operator=(Output&& outputObj) {

	value = outputObj.value;

	outputObj.value = nullptr;

	return *this;

}

/* 5
 +++++ DESTRUCTOR +++++
 */

Output::~Output() {

	if(value) delete value;

	value = nullptr;

}