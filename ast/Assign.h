#ifndef ASSIGN_H

#define ASSIGN_H

#include "ast_t.h"


class Assign {

private:

	ast_t *lValue;

	ast_t *rValue;

public:

	const ast_t& tempGetLeftVal() const {
		return *lValue; 
	}

	const ast_t& tempGetRightVal() const {
		return *rValue; 
	}

	/*
	 +++++ Accessors +++++
	 */
	const ast_t& getLeftOperand() const;

	const ast_t& getRightOperand() const;

	/*
	 +++++ MAIN C'TOR +++++
	 */
	Assign(ast_t&& lValueParam, ast_t&& rValueParam);


	/*
	 +++++ RULE OF FIVE +++++
	 */



	/* 1
	 +++++ COPY C'TOR +++++
	 */

	Assign(const Assign& assignObj) = delete;

	/* 2
	 +++++ MOVE C'TOR +++++
	 */

	Assign(Assign&& assignObj);

	/* 3
	 +++++ COPY ASSIGN +++++
	 */

	Assign& operator=(const Assign& assignObj) = delete;

	/* 4
	 +++++ MOVE ASSIGN +++++
	 */

	Assign& operator=(Assign&& assignObj);

	/* 5
	 +++++ DESTRUCTOR +++++
	 */
	~Assign();


}; // Assign

#endif