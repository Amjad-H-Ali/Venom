
#ifndef LIST_H

#define LIST_H

#include <vector>
#include "ast_t.h"


class List {

private:

	const std::vector<ast_t> *value;


public:

	const std::vector<ast_t>& tempGetVal() const {
		return *value;
	}


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

	List(const List& listObj) = delete;

	/* 2
	 +++++ MOVE C'TOR +++++
	 */
	List(List&& listObj);

	/* 3
	 +++++ COPY ASSIGN +++++
	 */
	List& operator=(const List& listObj) = delete;

	/* 4
	 +++++ MOVE ASSIGN +++++
	 */

	List& operator=(List&& listObj);

	/* 5
	 +++++ D'TOR +++++
	 */
	~List();


}; // List

#endif