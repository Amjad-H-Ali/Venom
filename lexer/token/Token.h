#ifndef TOKEN_H

#define TOKEN_H


#include <string>
#include <vector>



/*
 +++++ TOKEN_LIST takes in a Token Macro (T). Each Macro has the same +++++
 +++++ signature M(type, name), where type is a unique symbol for the +++++
 +++++ Token and nameis a string containing the Token. T: Token macro +++++
 */
 
#define TOKEN_LIST(T)							    \
	T(IS, "is")									    \
	T(IF, "if")										\
	T(EQ, "=")										\
	T(ADD, "+")										\
	T(BAR, "|")										\
	T(TAB, "\\t")									\
	T(EQEQ, "==")									\
	T(ELSE, "else")									\
	T(ELIF, "elif")									\
	T(COMMA, ",")									\
	T(ARROW, "=>")									\
	T(STRING, nullptr)								\
	T(OUTPUT, "output")								\
	T(NEWLINE, "\\n")								\
	T(LBRACKET, "[")								\
	T(RBRACKET, "]")								\
	T(LHANDLE, ":|")								\
	T(RHANDLE, "|:")								\
	T(BACKTICK, "`")								\
	T(ID, nullptr)						    
								



class Token {

public:


	/*
		*
		* All Token Symbols
		*
	*/
#define T(symbol, name) symbol,
	/* 
		* In this case, only the symbol is needed
		* and the second parameter is unused to
		* generate the List of Token Symbols.
	*/
	enum Symbol{TOKEN_LIST(T) NUM_OF_TOKENS};

#undef T


	

	/*
	 +++++ Array of const char *, which is all Token symbols in string form +++++
	 */

	static const char *typeName[NUM_OF_TOKENS];

	

	/*
		----------------
		  Constructors
		----------------
	*/

	/*
		*
		* IDENTIFIER and STRING Constructor.
		*
	*/
	Token(const std::string &stream, Symbol symType);

	/*
		*
		* Constructor for Everything else like keywords, operators, etc,
		*
	*/
	Token(Symbol symType);


	/*
		------------------
		  Getter methods
		------------------

	*/


	/*
		*
		* Gets the Token's symbol type in string form.
		*
	*/
	const char *getTypeName() const;

	/*
		*
		* Does this Token close off an array, block, or parameter list?
		*
	*/
	bool isClosing() const;

	std::vector<Token>::size_type getMatchingPair() const;

	/*
	 +++++ For Token::STRING or Token::ID Tokens. Everything else returns nullptr +++++
	 */
	std::string &getValue();


	/*
		------------------
		  Setter methods
		------------------

	*/

	void setClosing(bool isClosing);


	void setMatchingPair(std::vector<Token>::size_type otherPairIndx);


	/*
		------------------------
		  Overloaded Operators
		------------------------

	*/

	/*
		*
		* Overload operator to compare by symbol type.
		*
	*/
	bool operator==(Symbol typeToCompare) const;


private:

	/*
		*
		* This data member is set to nullptr unless type is a STRING or IDENTIFIER.
		*
	*/
	std::string value;

	/*
		*
		* Indicates that this Token is an end to a block, array, or parameter list.
		*
	*/
	bool closing;

	/*
		*
		* The matching opening/closing Token if this Token opens/closes an
		* array, block, or parameter list. Otherwise, set to nullptr.
		*
	*/
	std::vector<Token>::size_type matchingPair;



	Symbol type; 

}; // Token


#endif





