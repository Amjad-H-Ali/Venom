
#ifndef LIST_H

#define LIST_H

#include <vector>
#include "ast_t.h"


class List {

private:

	const std::vector<ast_t> *value;


public:
	/*
	 +++++ MAIN C'TOR +++++
	 */
	List(const std::vector<ast_t> *listValue);

	/* 
	 +++++ RULE OF FIVE +++++
	 */

	/* 1
	 +++++ COPY C'TOR +++++
	 */

	List(const List& listObj);

	/* 2
	 +++++ MOVE C'TOR +++++
	 */
	List(List&& listObj);

	/* 3
	 +++++ COPY C'TOR +++++
	 */
	List& operator=(const List& listObj);

	/* 4
	 +++++ MOVE C'TOR +++++
	 */

	List& operator=(List&& listObj);

	/* 5
	 +++++ D'TOR +++++
	 */
	~List();


}; // List

#endif