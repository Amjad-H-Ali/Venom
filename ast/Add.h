#ifndef ADD_H

#define ADD_H


#include "ast_t.h"



class Add {

private:

	ast_t *lOperand;

	ast_t *rOperand;


public:

	/*
	 +++++ MAIN C'TOR +++++
	 */
	
	Add(ast_t&& lOperandParam, ast_t&& rOperandParam);

	/*
	 +++++ RULE OF FIVE +++++
	 */

	/* 1
	 +++++ COPY C'TOR +++++
	 */

	Add(const Add& addObj);

	/* 2
	 +++++ MOVE C'TOR +++++
	 */

	Add(Add&& addObj);

	/* 3
	 +++++ COPY ASSIGN +++++
	 */

	Add& operator=(const Add& addObj);

	/* 4
	 +++++ MOVE ASSIGN +++++
	 */

	Add& operator=(Add&& addObj);
	
	/* 5
	 +++++ DESTRUCTOR +++++
	 */
	~Add();



}; // Add

#endif