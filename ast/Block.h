
#ifndef BLOCK_H

#define BLOCK_H

#include <vector>
#include "ast_t.h"




class Block {

private:

	const std::vector<ast_t> *value;


public:

	Block(const std::vector<ast_t> *blockValue);

	Block(Block&& blockObject);

	~Block();


}; // Block

#endif