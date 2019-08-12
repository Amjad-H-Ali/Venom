#ifndef BLOCK_DIMENSION_H

#define BLOCK_DIMENSION_H


#include "Dimension.h"





class BlockDimension : public Dimension {

private:

	BlockDimension()

		:Dimension()

	{};


public:


	// Ensures One Instance.
	static BlockDimension *getInstance() {

		static BlockDimension instance;

		return &instance;
	};


	// Copy or Assignment constructor not allowed in our Singleton.
	BlockDimension(const BlockDimension&) 	= delete; 
	void operator=(const BlockDimension&)	= delete;

}; // BlockDimension





#endif