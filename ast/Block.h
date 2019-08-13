
#ifndef BLOCK_H

#define BLOCK_H

#include <vector>
#include "ast_t.h"




class Block {

private:

	const std::vector<ast_t> *value;


public:

	/*
	 +++++ MAIN C'TOR +++++
	 */

	Block(const std::vector<ast_t> *blockValue);



	/*
	 +++++ RULE OF FIVE +++++
	 */



	/* 1
	 +++++ COPY C'TOR +++++
	 */

	Block(const Block& blockObj);

	/* 2
	 +++++ MOVE C'TOR +++++
	 */

	Block(Block&& blockObj);

	/* 3
	 +++++ COPY ASSIGN +++++
	 */

	Block& operator=(const Block& blockObj);

	/* 4
	 +++++ MOVE ASSIGN +++++
	 */

	Block& operator=(Block&& blockObj);

	/* 5
	 +++++ DESTRUCTOR +++++
	 */

	~Block();


}; // Block

#endif