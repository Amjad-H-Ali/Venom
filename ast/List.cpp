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

List::List(const List& listObj)
	:value(new std::vector<ast_t>(*listObj.value))
{}

/* 2
 +++++ MOVE C'TOR +++++
 */
List::List(List&& listObj)
	:value(listObj.value)
{

	listObj.value = nullptr;
}

/* 3
 +++++ COPY C'TOR +++++
 */
List& List::operator=(const List& listObj) {

	value = new std::vector<ast_t>(*listObj.value);
}

/* 4
 +++++ MOVE C'TOR +++++
 */

List& List::operator=(List&& listObj) {

	value = listObj.value;

	listObj.value = nullptr;
}

/* 5
 +++++ D'TOR +++++
 */
List::~List() {

	if(value) delete value;

	value = nullptr;
}