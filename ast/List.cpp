#include "List.h"
#include "AST.h"


List::List(const std::vector<ast_t> *listValue)
	:value(listValue)
{}

/*
 +++++ Move C'Tor +++++
 */
List::List(List&& listObj)
	:value(listObj.value)
{

	listObj.value = nullptr;
}

List::~List() {
	delete value;
}