#include "Block.h"
#include "AST.h"

/*
 +++++ MAIN C'TOR +++++
 */

Block::Block(const std::vector<ast_t> *blockValue)

	:value(blockValue)

{}



/*
 +++++ RULE OF FIVE +++++
 */



/* 1
 +++++ COPY C'TOR +++++
 */

// Block::Block(const Block& blockObj) 

// 	:value(new std::vector<ast_t>(*blockObj.value))
// {}

/* 2
 +++++ MOVE C'TOR +++++
 */

Block::Block(Block&& blockObj)
	:value(blockObj.value)
{

	blockObj.value = nullptr;
}

/* 3
 +++++ COPY ASSIGN +++++
 */

// Block& Block::operator=(const Block& blockObj) {

// 	value = new std::vector<ast_t>(*blockObj.value);

// 	return *this;
// }

/* 4
 +++++ MOVE Block +++++
 */

Block& Block::operator=(Block&& blockObj) {

	value = blockObj.value;

	blockObj.value = nullptr;

	return *this;

}

/* 5
 +++++ DESTRUCTOR +++++
 */

Block::~Block() {

	if(value) delete value;

	value = nullptr;
}

