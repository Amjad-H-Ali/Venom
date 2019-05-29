#ifndef DIMENSION_H

#define DIMENSION_H

#include "Token.h"

#include <iostream>

class Dimension {

private:

	struct Link  {

		token::TokenNode *tn;

		Link *next, *prev;
	};

	// Dimension
	int D = 0;

	// Linked-List of Openings and 
	// closings To Dimension.
	Link *opening, *closing;

	Dimension()
		:opening(nullptr), closing(nullptr)
	{};

public:

	void insertOpen(const token::TokenNode &tn) {

		Link *newOpen = new Link();

		newOpen->tn = tn;

		newOpen->next = opening;

		if(opening) newOpen->next->prev = newOpen;

		opening = newOpen;

		d++;
	}


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