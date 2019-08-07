#ifndef BLOCK_H

#define BLOCK_H




class Block {

private:

	const std::vector<ast_t> &value;


public:

	Block(const std::vector<ast_t> &blockValue)

		:value(blockValue)

	{}


}; // Block



#endif