#ifndef DIMENSION_H

#define DIMENSION_H

#include "Token.h"

#include <iostream>

class Dimension {

private:

	struct Link  {

		const token::TokenNode *tn;

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

	void insertOpen(const token::TokenNode *tn) {

		Link *newOpen = new Link();

		newOpen->tn = tn;

		newOpen->next = opening;

		// Set neighbor prev to point to newOpen node.
		if(opening) newOpen->next->prev = newOpen;

		opening = newOpen;

		D++; // Increment Dimension
	}

	void insertClose(const token::TokenNode *tn) {

		Link *newClose = new Link();

		newClose->tn = tn;

		newClose->next = opening;

		// Set neighbor prev to point to newClose node.
		if(closing) newClose->next->prev = newClose;

		closing = newClose;

		D--; // Decrement Dimension
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