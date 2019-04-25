// #include <iostream>
// #include <fstream>
// #include <stdint.h>

// using namespace std;

// #define TOKEN_LIST(T, K)\
// T(MJ, "Ali", 9)
// #define T(name, string, precedence) name,
// 	enum Value { TOKEN_LIST(T, T) NUM_TOKENS };
// char multi_peek(ifstream &in, int places);

// int main() {



	
// cout << NUM_TOKENS << endl;

// 	ifstream in;
// 	in.open("new.vnm");
// 	in >> noskipws;
// 	char c;
// 	in >>ws >> c >> ws>> c >> c >> c;
// 	cout << c << endl;
// 	char a = multi_peek(in,4);
// 	cout << a << endl;




// }


// char multi_peek(ifstream &in, int places) {
// 	char result;
// 	streampos start_pos = in.tellg();
	
// 	for(int i = 0; i < places; i ++) {
// 		in >> ws >> result;
// 	}
// 	in.seekg(start_pos);

// 	return result;
// };


//  