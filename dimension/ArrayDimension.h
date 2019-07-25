#ifndef ARRAYDIMENSION_H

#define ARRAYDIMENSION_H

#include "Dimension.h"


#include <iostream>



class ArrayDimension : public Dimension {

private:

	ArrayDimension()
	
		:Dimension()
	{};


public:


	// Ensures One Instance.
	static ArrayDimension *getInstance() {

		static ArrayDimension instance;

		return &instance;
	};


	// Copy or Assignment constructor
	// not allowed in our Singleton.
	ArrayDimension(const ArrayDimension&) 	= delete; 
	void operator=(const ArrayDimension&)	= delete;

}; // ArrayDimension


#endif