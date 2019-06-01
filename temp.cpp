// #include <iostream>
// #include <fstream>
// #include "Dimension.h"
// #include "Token.h"

// Dimension *const D = Dimension::getInstance();

// // Determines if TokenNode Closes Dimension.
// bool isClosing(INFILE in) {

// 	if(D->singleLine) {
// 		unsigned jumps;

// 		*D >> jumps;


// 		char result;
// 		char container; 

// 		// To remember starting position
// 		auto startPos = in.tellg();

// 		in >> std::noskipws;

// 		// Skip ahead and peek.
// 		for(unsigned i = 0; in >> container && i < jumps-1; i ++) {

// 			// EOF 
// 			if(in.eof()) break;

// 			// To Skip Spaces ' ' 0x20, but not other ws.
// 			if(container == ' ') {i--; continue;}

// 			// If comma in between, it's closing.
// 			if(container == ',') return true;

// 			result = container;
// 		}

			
// 		if(result == '\n' || in.eof()) return true;

// 		// Return to start position
// 		in.seekg(startPos);
// 	}


// 	return false;


// 	// else if not singleLine
// 	// 	peek(D) != Tab or in between is comma return true

// 	// return false 

// }

// int main() {



// 	token::TokenNode *tn = new token::TokenNode;

	



// 	std::ifstream in("new.vnm");
// 	char c;

// 	in>>c;
// 	D->insertOpen(tn);



// 	in>>c;
// 	D->insertOpen(tn);
// 	in>>c;
// 	D->insertClose(tn);

// 	in >> c;
// 	D->insertClose(tn);

// 	unsigned j;

// 	*D >> j;

// 	std:: cout << "This is J:" << j << std::endl;
	

// 	if(isClosing(in)) {

// 		D->insertClose(tn);
// 		std::cout << "CLOSING" << std::endl;

// 	} 
// 	else {

// 		D->insertOpen(tn);
// 	 	std::cout << "OPENING" << std::endl;
// 	}
	

// 	std::cout << c << std::endl;



// 	// std::cout << "Yes" << std::endl;

// 	// Dimension *const d = Dimension::getInstance();

	

// 	// token::TokenNode *tn2 = new token::TokenNode;

// 	// token::TokenNode *tn3 = new token::TokenNode;

// 	// token::TokenNode *tn4 = new token::TokenNode;

// 	// token::TokenNode *tn5 = new token::TokenNode;

// 	// token::TokenNode *tn6 = new token::TokenNode;

	

// 	// d->insertOpen(tn2);

// 	// d->insertOpen(tn3);

// 	// d->insertOpen(tn4);

// 	// d->insertOpen(tn5);

// 	// d->insertOpen(tn5);

// 	// d->insertOpen(tn5);

// 	// d->insertOpen(tn5);

// 	// d->insertOpen(tn5);

// 	// d->insertOpen(tn5);

// 	// d->insertOpen(tn5);

// 	// d->insertOpen(tn5);

// 	// d->insertOpen(tn5);

// 	// d->insertOpen(tn5);

// 	// d->insertClose(tn6);


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

// };



