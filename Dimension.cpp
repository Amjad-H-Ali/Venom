#include "Dimension.h"
#include "Token.h"


// Class for Link in Linked-List
struct Dimension::Link {

	const token::TokenNode *tn;

	Link *next, *prev;
};

// Insert Opening of a new Dimension into Link.
void Dimension::insertOpen(const token::TokenNode *tn) {

	Link *newOpen = new Link();

	newOpen->tn = tn;

	newOpen->next = opening;

	// Set neighbor prev to point to newOpen node.
	if(opening) newOpen->next->prev = newOpen;
	else openingT = newOpen; // Set Tail pointer to Last Node.

	opening = newOpen;

	D++; // Increment Dimension
};

// Insert Closing of a Dimension into Link.
void Dimension::insertClose(const token::TokenNode *tn) {

	Link *newClose = new Link();

	newClose->tn = tn;

	newClose->next = opening;

	// Set neighbor prev to point to newClose node.
	if(closing) newClose->next->prev = newClose;
	else closingT = newClose; // Set Tail pointer to Last Node.

	closing = newClose;

	D--; // Decrement Dimension
};




