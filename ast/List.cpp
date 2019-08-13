#include "List.h"
#include "AST.h"

/*
 +++++ MAIN C'TOR +++++
 */
List::List(const std::vector<ast_t> *listValue)
	:value(listValue)
{}

/* 
 +++++ RULE OF FIVE +++++
 */

/* 1
 +++++ COPY C'TOR +++++
 */

// List::List(const List& listObj)
// 	:value(new std::vector<ast_t>(*listObj.value))
// {}

/* 2
 +++++ MOVE C'TOR +++++
 */
List::List(List&& listObj)
	:value(listObj.value)
{

	listObj.value = nullptr;
}

/* 3
 +++++ COPY ASSIGN +++++
 */
// List& List::operator=(const List& listObj) {

// 	value = new std::vector<ast_t>(*listObj.value);

// 	return *this;
// }

/* 4
 +++++ MOVE ASSIGN +++++
 */

List& List::operator=(List&& listObj) {

	value = listObj.value;

	listObj.value = nullptr;

	return *this;
}

/* 5
 +++++ D'TOR +++++
 */
List::~List() {

	if(value) delete value;

	value = nullptr;
}