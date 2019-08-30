
#include <iostream>
#include <variant>
#include "./lexer/token/Token.h"
#include "./lexer/Lexer.h"
#include "./ast/ast_t.h"
#include "./ast/AST.h"
#include "./parser/Parser.h"
#include "./vm/bytecode/Bytecode.h"
#include "./vm/bytecode/BytecodeCompiler.h"

// template<typename ... Params> struct _Overloads : Params ... {using Params::operator()...;};
// template<typename ... Params> _Overloads(Params...) -> _Overloads<Params...>;




// template<typename ... Params>
// void _log (Params&& ... params) {
//     std::visit(_Overloads{

//         [](const auto&){std::cout << "Auto" << std::endl;},
//         [](const AST<Output>&n){
//             std::cout << "Output" << std::endl;
//             _log(n.getValue().getValue());

//         },

//         [](const AST<Add>&n){

//             std::cout << "Add" << std::endl;
//             _log(n.getValue().getLeftOperand());
//             _log(n.getValue().getRightOperand());

//         },
//         [](const AST<Func>&n){

//             std::cout << "Func" << std::endl;

//             for(const ast_t& a : n.getValue().getParamList().getValue())
//                 _log(a);
//             for(const ast_t& a : n.getValue().getBody().getValue())
//                 _log(a);

//         },
//         [](const AST<Assign>&n){

//             std::cout << "Assign" << std::endl;

//             _log(n.getValue().getLeftOperand());
//             _log(n.getValue().getRightOperand());

//         },
//         [](const AST<Call>&n){

//             std::cout << "Call" << std::endl;


//         },
//         [](const AST<Write>&n){std::cout << "Write" << std::endl;},

//         [](const AST<Num>&n){std::cout << "Num" << std::endl;},


//         [](const AST<ID>&n){std::cout << "ID" << std::endl;}





//     }, std::forward<Params>(params)...);
// }


int main(){


   /*
    +++++ Tokenize ++++
    */
    Lexer tokenize("new.venom");

    std::vector<Token>& tokenVec = tokenize();


    /*
     +++++ Parse Tokens into AST ++++
     */
    Parser parser(tokenVec);

    decltype(auto) parse = parser();
    
    std::vector<ast_t>& astVec = parse(

        [&parser,&tokenVec]{
            
            return &tokenVec[parser.getCurr()] != &(*tokenVec.end());
        }
    );


    /*
     +++++ Compile AST vector into Bytecode +++++
     */
    std::vector<Bytecode>& bytecodeVec = BytecodeCompiler(astVec)();

 
    VM vm(&bytecodeVec);

    vm();



};

