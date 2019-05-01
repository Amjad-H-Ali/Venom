// #include <iostream>
// #include <stdint.h>


// #define TOKEN_LIST(T, S)	   	\
// 	T(STRING, isSTRING(S))	\
// 	T(EQEQ, isEQEQ(S))		\
// 	T(IF, isIF(S))			


// bool isMatch (char *str1, char *str2) {
// 	int i = 0;
// 	std::cout << "ooo" << std::endl;

// 	while(str1[i] == str2[i]) { 

// 		if(str1[i] == '\0' || str2[i] == '\0' ) return true;	
// 		i++;
// 	}

// 	return false;
// };
// bool isSTRING(char *str) {
// 	std::cout << "ooo" << std::endl;
// 	if(str[0] == '"') return true;
// }
// bool isEQEQ(char *str) {
// 	if(isMatch(str, (char *) "==")) return true;
// }
// bool isIF(char *str) {
// 	if(isMatch(str, (char *) "if")) return true;
// }

// struct Token {
// #define T(type, name) type, 
// 		enum Value {TOKEN_LIST(T, S) NUM_OF_TOKENS};
// #undef T

// 	Token(char *str) {
// #define T(type, name) if(name) { std::cout << #type << std::endl;}
// 	TOKEN_LIST(T, str)
// #undef T
// 	};


// 	Value type;
// 	char *name;


// };

// char *foo(char *str) {
// #define T(type, name) type, 
// 		enum Value {TOKEN_LIST(T, S) NUM_OF_TOKENS};
// #undef T

// #define T(type, name) if(name) return (char*)#type;
// 	TOKEN_LIST(T, str)
// #undef T

// };

// int main() { 



// 	std::cout << foo((char *)"\"if\"") << std::endl;


// }

 