/*
	* ActionMap will be used as a node in a Linked-List.
	* This List Includes The Address Of Only The "Action" Tokens ...
	* From The Linked-List of TokenNodes That Parser Will Need in ...
	* order to Map to and Parse said Token. Such Tokens Include ...
	* Operators, Key Words, and that is all I can think of as of now.
*/

#pragma once

#include "Token.h" 

namespace actMap{


struct ActionMap {
	// Points to Action Node in 
	token::TokenNode *mapValue;

	actMap::ActionMap *next, *prev;

	ActionMap() 
		:mapValue(nullptr)
	{};

	~ActionMap() {
		// Detach from Link
		if(prev) prev->next = nullptr;
		if(next) next->prev = nullptr;
	}
};


// Linked-List Head Declaration
extern ActionMap *head;

// Linked-List Tail Declaration
extern ActionMap *tail;


}; // actMap 


