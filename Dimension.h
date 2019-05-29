#ifndef DIMENSION_H

#define DIMENSION_H


class Dimension {

private:

	struct Opening;

	struct Closing;

	Dimension(){};

public:

	// Dimension
	int D = 0;



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