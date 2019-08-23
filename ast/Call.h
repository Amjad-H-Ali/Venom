

#ifndef CALL_H

#define CALL_H


#include "ast_t.h"


class Call {

private:

	ast_t *lOperand;

	const std::vector<ast_t> *argList;


public:

	/*
	 +++++ Accessors +++++
	 */
	const ast_t& getLeftOperand() const;

	const std::vector<ast_t>& getArgList() const;

	/*
	 +++++ MAIN C'TOR +++++
	 */
	Call(ast_t&& lOperandParam, const std::vector<ast_t> *argListParam);

	/*
	 +++++ RULE OF FIVE +++++
	 */

	/* 1
	 +++++ COPY C'TOR +++++
	 */

	Call(const Call& callObj) = delete;

	/* 2
	 +++++ MOVE C'TOR +++++
	 */

	Call(Call&& callObj);

	/* 3
	 +++++ COPY ASSIGN +++++
	 */

	Call& operator=(const Call& callObj) = delete;

	/* 4
	 +++++ MOVE ASSIGN +++++
	 */

	Call& operator=(Call&& callObj);
	
	/* 5
	 +++++ DESTRUCTOR +++++
	 */
	~Call();

}; // Call


#endif