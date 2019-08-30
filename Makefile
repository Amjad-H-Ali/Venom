all: venom

	


venom: 
	g++ -std=c++2a -o venom *.cpp dimension/*.cpp lexer/token/*.cpp lexer/*.cpp parser/*.cpp ast/*.cpp vm/bytecode/*.cpp vm/*.cpp