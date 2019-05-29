#include <iostream>
#include "Dimension.h"



int main() {


	Dimension *d = Dimension::getInstance();

	std::cout << d << std::endl;

	Dimension *b = Dimension::getInstance();

	Dimension *e = Dimension::getInstance();

	std::cout << d << std::endl;
	std::cout << b << std::endl;
	std::cout << e << std::endl;


};



