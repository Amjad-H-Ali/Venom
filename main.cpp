
#include <iostream>
#include <variant>
#include "./lexer/token/Token.h"
#include "./lexer/Lexer.h"
#include "./ast/ast_t.h"
#include "./ast/AST.h"
#include "./parser/Parser.h"
#include "./vm/bytecode/Bytecode.h"
#include "./vm/bytecode/BytecodeCompiler.h"


template<typename ... Params> struct AstOverloads : Params ... {using Params::operator()...;};

template<typename ... Params> AstOverloads(Params ...) -> AstOverloads<Params ...>;


void log(const ast_t& ast_tObj) {

    std::visit(AstOverloads {

        [](const auto& astObj) {std::cout << "Don't Know!" <<std::endl;},

        [](const AST<ID>& astObj) {
            std::cout << "AST<ID>" <<std::endl;
        },

        [](const AST<Str>& astObj) {
            std::cout << "AST<Str>" <<std::endl;
        },

        [](const AST<List>& astObj) {

            std::cout << "AST<List>" <<std::endl;

            const std::vector<ast_t>& list = astObj.tempGetVal().tempGetVal();

            std::cout << "[" << std::endl;

            for(const auto& astElem : list) {

                std::cout << "  ";

                log(astElem);
            }

            std::cout << "]" << std::endl;
        },

        [](const AST<Block>& astObj) {
            std::cout << "AST<Block>" <<std::endl;

            const std::vector<ast_t>& block = astObj.tempGetVal().tempGetVal();

            std::cout << ":|" << std::endl;

            for(const auto& astElem : block) {

                std::cout << "  ";

                log(astElem);
            }

            std::cout << "|:" << std::endl;
        },

        [](const AST<Assign>& astObj) {
            std::cout << "AST<Assign>" <<std::endl;

            log(astObj.tempGetVal().tempGetLeftVal());

            std::cout << "=" <<std::endl;

            log(astObj.tempGetVal().tempGetRightVal());

        },

        [](const AST<Add>& astObj) {
            std::cout << "AST<Add>" <<std::endl;
            
            log(astObj.tempGetVal().tempGetLeftVal());

            std::cout << "+" <<std::endl;

            log(astObj.tempGetVal().tempGetRightVal());
        },

        [](const AST<Func>& astObj) {
            std::cout << "AST<Func>" <<std::endl;

            const std::vector<ast_t>& params = astObj.tempGetVal().tempGetParams().tempGetVal();

            std::cout << "[" << std::endl;

            for(const auto& astElem : params) {

                std::cout << "  ";

                log(astElem);
            }

            std::cout << "]" << std::endl;


            const std::vector<ast_t>& block = astObj.tempGetVal().tempGetBody().tempGetVal();

            std::cout << ":|" << std::endl;

            for(const auto& astElem : block) {

                std::cout << "  ";

                log(astElem);
            }

            std::cout << "|:" << std::endl;

        }

    }, ast_tObj);
} 


/*

    AST<ASSIGN>( AST<ID>(foo), AST<Func>( List(name,age), Block(ADD(name,age)) ) ) )

    Fund Def:
    
        + Loop param list of AST<ID>(vector of ast_t)
        + Compile AST<ID> into ByteCode:
          + AST<ID> Compiles to:
            + DECL {ID value} 
        + Loop block (vector of ast_t)
        + Compile AST<Add> into ByteCode:
          + AST<Add> Compiles to:
            +


        





*/


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

