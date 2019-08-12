#include "Block.h"
#include "AST.h"


Block::Block(const std::vector<ast_t> *blockValue)

	:value(blockValue)

{}

Block::Block(Block&& blockObject)

	:value(blockObject.value)
{
	blockObject.value = nullptr;
}

Block::~Block() {
	delete value;
}