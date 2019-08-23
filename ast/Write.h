#ifndef WRITE_H

#define WRITE_H

/*
 ++++ TODO: SIMILAR TO OUTPUT ++++
 */


#include "ast_t.h"



class Write {

private:

	ast_t *value;

public:

	/*
	 +++++ Accessors +++++
	 */
	const ast_t& getValue() const;

	/*
	 +++++ MAIN C'TOR +++++
	 */

	Write(ast_t&& valueParam);

	/*
	 +++++ RULE OF FIVE +++++
	 */

	/* 1
	 +++++ COPY C'TOR +++++
	 */

	Write(const Write& writeObj) = delete;

	/* 2
	 +++++ MOVE C'TOR +++++
	 */

	Write(Write&& writeObj);

	/* 3
	 +++++ COPY ASSIGN +++++
	 */

	Write& operator=(const Write& writeObj) = delete;

	/* 4
	 +++++ MOVE ASSIGN +++++
	 */

	Write& operator=(Write&& writeObj);
	
	/* 5
	 +++++ DESTRUCTOR +++++
	 */
	~Write();



}; // Write

#endif