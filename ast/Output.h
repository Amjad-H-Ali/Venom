#ifndef OUTPUT_H

#define OUTPUT_H


#include "ast_t.h"



class Output {

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

	Output(ast_t&& valueParam);

	/*
	 +++++ RULE OF FIVE +++++
	 */

	/* 1
	 +++++ COPY C'TOR +++++
	 */

	Output(const Output& outputObj) = delete;

	/* 2
	 +++++ MOVE C'TOR +++++
	 */

	Output(Output&& outputObj);

	/* 3
	 +++++ COPY ASSIGN +++++
	 */

	Output& operator=(const Output& outputObj) = delete;

	/* 4
	 +++++ MOVE ASSIGN +++++
	 */

	Output& operator=(Output&& outputObj);
	
	/* 5
	 +++++ DESTRUCTOR +++++
	 */
	~Output();



}; // Output

#endif