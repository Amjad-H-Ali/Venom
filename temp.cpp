// #include <iostream>
// #include <fstream>

// using namespace std;
// char multi_peek(ifstream &in, int places);

// int main() {


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