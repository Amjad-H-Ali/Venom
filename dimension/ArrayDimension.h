#ifndef ARRAY_DIMENSION_H

#define ARRAY_DIMENSION_H

#include "Dimension.h"




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