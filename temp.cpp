// // #include <iostream>
// // #include <fstream>
// // #include "ArrayDimension.h"
// // #include "BlockDimension.h"
// // #include "Token.h"

// // ArrayDimension *const D = ArrayDimension::getInstance();

// // BlockDimension *const B = BlockDimension::getInstance();


// // #include "Token.h"
// // #include "AST.h"
// // #include "AST_Func.h"
// // #include "AST_Node.h"
// // #include "AST_List.h"
// // #include "AST_Block.h"

// #include <iostream>

// template<typename Callable, typename ... Params> 
// auto foo(Callable call, Params ... params) {

//     return [=](){
//         return call(params...);
//     };
// };

// int add(int num1, int num2) {
//     return num1 + num2;
// }

// int main () {
//    auto l = foo(add, 1, 4);

//    std::cout << l();


// }
// // #include <iostream>

// // #include "AST_List.h"
// // #include "AST_Block.h"
// // #include "AST_Func.h"

// // void foo(AST_Func *f) {
// // 	std::cout << "I'm function " << std::endl;
// // };

// // void foo(AST_List *l) {
// // 	std::cout << "I'm list " << std::endl;
// // };

// // int main() {


// // 	AST *head = nullptr;

// // 	AST *newNode = new AST;

// // 	newNode->node.func = new AST_Func(ast::FUNC, nullptr, nullptr);

// // 	AST *newNode2 = new AST;

// // 	newNode2->node.list = new AST_List(ast::LIST, nullptr);

// // 	newNode->next = newNode2;

// // 	foo(newNode2->node.list);
// // };
	


// // 	// std::cout << "Yes" << std::endl;

// 	// ArrayDimension *const d = ArrayDimension::getInstance();
// 	// BlockDimension *const b = BlockDimension::getInstance();

	

// 	// token::TokenNode *tn = new token::TokenNode;

// 	// token::TokenNode *tn2 = new token::TokenNode;

// 	// token::TokenNode *tn3 = new token::TokenNode;

// 	// token::TokenNode *tn4 = new token::TokenNode;

	

// 	// D->insertOpen(tn);
// 	// d->insertClose(tn);


// 	// d->insertOpen(tn);
// 	// d->insertClose(tn);

// 	// d->insertOpen(tn);
// 	// d->insertClose(tn);


// 	// D->insertOpen(tn);
// 	// d->insertClose(tn);





// 	// b->insertOpen(tn);
// 	// B->insertClose(tn);


// 	// b->insertOpen(tn2);
// 	// B->insertClose(tn2);

// 	// B->insertOpen(tn3);
// 	// B->insertClose(tn3);


// 	// B->insertOpen(tn4);
// 	// b->insertClose(tn4);


// 	// auto n = b->getCurrentOpen();

// 	// auto z = b->getCurrentOpen();

// 	// auto w = b->getCurrentOpen();

// 	// std::cout << n << std::endl;
// 	// std::cout << z << std::endl;
// 	// std::cout << w << std::endl;


// 	// d->insertOpen(tn2);
// 	// d->insertClose(tn6);


// 	// d->insertOpen(tn3);
// 	// d->insertClose(tn6);


// // 	// unsigned i;

// // 	// *d>>i;

// // 	// if(*d == 8)
// // 	// 	std::cout << "It's 8" << std::endl;
// // 	// else if(*d < 8)
// // 	// 	std::cout << "Less than 8" << std::endl;

// // 	// else if(*d <= 10)
// // 	// 	std::cout << "Less than eq to 10" << std::endl;

// // 	// else if(*d > 12)
// // 	// 	std::cout << "Greater than 11" << std::endl;

// // 	// else if(*d >= 11)
// // 	// 	std::cout << "Greater than eq to 11" << std::endl;


// // 	// std::cout << i << std::endl;

// //};



