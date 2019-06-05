#include <iostream>
#include <fstream>
#include "ArrayDimension.h"
#include "BlockDimension.h"
#include "Token.h"

ArrayDimension *const D = ArrayDimension::getInstance();

BlockDimension *const B = BlockDimension::getInstance();



int main() {


	


// 	// std::cout << "Yes" << std::endl;

	ArrayDimension *const d = ArrayDimension::getInstance();
	BlockDimension *const b = BlockDimension::getInstance();

	

	token::TokenNode *tn = new token::TokenNode;

	token::TokenNode *tn2 = new token::TokenNode;

	token::TokenNode *tn3 = new token::TokenNode;

	token::TokenNode *tn4 = new token::TokenNode;

	

	D->insertOpen(tn);
	d->insertClose(tn);


	d->insertOpen(tn);
	d->insertClose(tn);

	d->insertOpen(tn);
	d->insertClose(tn);


	D->insertOpen(tn);
	d->insertClose(tn);





	b->insertOpen(tn);
	B->insertClose(tn);


	b->insertOpen(tn2);
	B->insertClose(tn2);

	B->insertOpen(tn3);
	B->insertClose(tn3);


	B->insertOpen(tn4);
	b->insertClose(tn4);


	auto n = b->getCurrentOpen();

	auto z = b->getCurrentOpen();

	auto w = b->getCurrentOpen();

	std::cout << n << std::endl;
	std::cout << z << std::endl;
	std::cout << w << std::endl;


	// d->insertOpen(tn2);
	// d->insertClose(tn6);


	// d->insertOpen(tn3);
	// d->insertClose(tn6);


// 	// unsigned i;

// 	// *d>>i;

// 	// if(*d == 8)
// 	// 	std::cout << "It's 8" << std::endl;
// 	// else if(*d < 8)
// 	// 	std::cout << "Less than 8" << std::endl;

// 	// else if(*d <= 10)
// 	// 	std::cout << "Less than eq to 10" << std::endl;

// 	// else if(*d > 12)
// 	// 	std::cout << "Greater than 11" << std::endl;

// 	// else if(*d >= 11)
// 	// 	std::cout << "Greater than eq to 11" << std::endl;


// 	// std::cout << i << std::endl;

};



