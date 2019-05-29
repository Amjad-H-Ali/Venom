#ifndef DIMENSION_H

#define DIMENSION_H

#include "Token.h"

#include <iostream>

class Dimension {

private:

	struct Link;

	// Dimension
	int D = 0;

	// Linked-List of Openings and 
	// closings To Dimension.
	Link *opening,  *closing,
		 *openingT, *closingT; // Tail pointers.

	Dimension()
		:opening(nullptr), closing(nullptr), openingT(nullptr), closingT(nullptr)
	{};

public:
	// Insert Opening of a new Dimension into Link.
	void insertOpen(const token::TokenNode *tn);

	// Insert Closing of a Dimension into Link.
	void insertClose(const token::TokenNode *tn);

	static Dimension *getInstance() {

		static Dimension instance;

		return &instance;
	};

	// Copy or Assignment constructor
	// not allowed for our Singleton.
	Dimension(const Dimension&) 		= delete; 
	void operator=(const Dimension&)	= delete;
};


#endif