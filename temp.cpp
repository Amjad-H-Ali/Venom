// #include <iostream>
// #include <fstream>

// typedef std::ifstream &INFILE;


// // Checks if current character is a letter.
// bool isAtoZ(char c) {
// 	return ((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z'));
// };


// bool isAtoZ2(char c) {

	

	

// 	return (  ( ~(((c - 'a') >>31) | (('z' - c) >>31))) || (~(((c - 'A') >>31) | (('Z' - c) >>31))) );
// };


// // Checks if character is an eligible beggining for AlphaNumeric.
// bool isEligibleStartToAlphaNum(char c) {
// 	return (isAtoZ(c) );
// };


// bool isEligibleStartToAlphaNum2(char c) {
// 	return (isAtoZ2(c) );
// };

// // of this file object, and the range of characters to read.
// char *makeC_String(INFILE in, std::streampos range) {

// 	// Make a C String.
// 	char *name = new char[range+(decltype(in.tellg()))1];

// 	// Read in to name.
// 	in.read(name, range);

// 	name[range] = '\0';


// 	return name;
// };  

// // of this file object, and the range of characters to read.
// char *makeC_String2(INFILE in, std::streampos range) {

// 	// Make a C String.
// 	char *name = new char[range+(decltype(in.tellg()))1];

// 	// Read in to name.
// 	in.read(name, range);

// 	name[range] = '\0';


// 	return name;
// };

// // Determines the length of stream to chomp based on the 
// // Bool Function passed in as argument. Restores file pointer
// // to original position when finished.
// std::streampos rangeToChomp(char &c, INFILE in, bool(*greenLight)(const char)) {

// 	decltype(in.tellg()) startPos = in.tellg(), offset = 0, endPos, range;

// 	while(greenLight(c) && !in.eof()) {

// 		offset+= (decltype(in.tellg()))1;
// 		in>>c;

// 	}

// 	endPos = startPos + offset;
// 	range = endPos - startPos;

// 	// Reset file pointer to original position.
// 	in.clear();
// 	in.seekg(startPos-(decltype(in.tellg()))1, in.beg);

// 	return range;
// };

// // Gets whole AlphaNumeric from beginning to end.
// char *chompAlphaNumeric(char &c, INFILE in) {

// 	// Range to Chomp
// 	auto range = rangeToChomp(c, in, &isAtoZ);

// 	return makeC_String(in, range);
// };

// // Gets whole AlphaNumeric from beginning to end.
// char *chompAlphaNumeric2(char &c, INFILE in) {


// 	// Range to Chomp
// 	auto range = rangeToChomp(c, in, &isAtoZ2);


// 	return makeC_String2(in, range);
// };

// int main(){






//   std::ifstream in2("test.txt");

//     char c2;

//     in2 >> std::noskipws;

//     std::clock_t time2;

//     time2 = std::clock();
//     while(in2 >> c2) {

//     	if(isEligibleStartToAlphaNum2(c2))
//     		chompAlphaNumeric2(c2, in2);


//     }

//     time2 = std::clock() - time2;

//     std::cout << (float)time2/CLOCKS_PER_SEC << std::endl;








//     std::ifstream in("test.txt");

//     char c;

//     in >> std::noskipws;

//     std::clock_t time;

//     time = std::clock();
//     while(in >> c) {

//     	if(isEligibleStartToAlphaNum(c))
//     		chompAlphaNumeric(c, in);


//     }

//     time = std::clock() - time;

//     std::cout << (float)time/CLOCKS_PER_SEC << std::endl;





 


 
  



// }

// /*
// 	C-String

// 	2.95 sec for small

// */




