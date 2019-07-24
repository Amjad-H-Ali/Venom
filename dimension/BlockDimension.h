#ifndef BLOCKDIMENSION_H

#define BLOCKDIMENSION_H


#include "Dimension.h"


#include <iostream>



class BlockDimension : public Dimension {

private:

	BlockDimension()
		:Dimension()
	{std::cout << "BlockDimension Was Created!" << " Address: " << this <<  std::endl;};


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