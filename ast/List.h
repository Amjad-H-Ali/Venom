
#ifndef LIST_H

#define LIST_H

#include <vector>
#include "ast_t.h"


class List {

private:

	const std::vector<ast_t> *value;


public:

	List(const std::vector<ast_t> *listValue);

	/*
	 +++++ Move C'Tor +++++
	 */
	List(List&& listObj);

	~List();


}; // List

#endif