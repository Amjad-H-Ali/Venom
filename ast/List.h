#ifndef LIST_H

#define LIST_H




class List {

private:

	const std::vector<ast_t> &value;


public:

	List(const std::vector<ast_t> &listValue)
		:value(listValue)
	{}


}; // List



#endif