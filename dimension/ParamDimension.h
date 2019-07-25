#ifndef ParamDIMENSION_H

#define ParamDIMENSION_H

#include "Dimension.h"


#include <iostream>



class ParamDimension : public Dimension {

private:

	ParamDimension()

		:Dimension()

	{};


public:


	// Ensures One Instance.
	static ParamDimension *getInstance() {

		static ParamDimension instance;

		return &instance;
	};


	// Copy or Assignment constructor
	// not allowed in our Singleton.
	ParamDimension(const ParamDimension&) 	= delete; 
	void operator=(const ParamDimension&)	= delete;

}; // ParamDimension


#endif