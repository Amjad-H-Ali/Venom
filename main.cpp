
#include <iostream>
#include "./lexer/token/Token.h"
#include "./lexer/Lexer.h"
#include "./ast/ast_t.h"
#include "./ast/AST.h"
#include "./parser/Parser.h"



int main(){


   
    Lexer tokenize("new.venom");

    std::vector<Token>& tokenVec = tokenize();

    for(const auto& token : tokenVec)

        std::cout << token.getTypeName()  << std::endl;

    Parser parser(tokenVec);

    decltype(auto) parse = parser();
    
    std::vector<ast_t>& astVec = parse(

        [&parser,&tokenVec]{
            
            return &tokenVec[parser.getCurr()] != &(*tokenVec.end());
        }
    );

    for(const auto& elem:astVec)
        std::cout << "AST" << std::endl;

};

