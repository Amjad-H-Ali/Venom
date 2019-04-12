// #include <iostream>
// #include <fstream>

// using namespace std;

// void parse_string(string &s, ifstream &in) {
// 	string left_over;
// 	int last_indx = s.length() - 1;

// 	while(s[last_indx] != '\'' && s[last_indx] != '"') {
// 		in >> left_over;
// 		s+= left_over;
// 		last_indx = s.length() - 1;
// 	}
// };
// int main() {

// 	ifstream in;

// 	in.open("new.vnm");

// 	string c;

// 	in >> c;

// 	parse_string(c, in);

// 	cout << c << endl;

// }