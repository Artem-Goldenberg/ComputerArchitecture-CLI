#include "parser.h"
#include <iostream>

int main() {
    // init test input
    Parser parser;
    std::vector<Token> in_tokens; // g++ lib.hpp -o lib.so |
    in_tokens.push_back(Token(TokenType::mString, "g++"));
    in_tokens.push_back(Token(TokenType::mString, "lib.hpp"));
    in_tokens.push_back(Token(TokenType::mString, "-o"));
    in_tokens.push_back(Token(TokenType::mString, "lib.so"));
    in_tokens.push_back(Token(TokenType::mPipe, ""));

    // get parser results
    std::variant<std::vector<CommandData>, std::string> var_ans = parser.parse(in_tokens);
    if( std::holds_alternative<std::string>(var_ans) ) {
        if(std::get<std::string>(var_ans) == "nowhere to transfer") {
            return 0;
        }
        std::cout << "Parse error: " << std::get<std::string>(var_ans) << ", but expected error: nowhere to transfer" << std::endl;
        return 1;
    }

    std::cout << "Parser expected to fail, but passed" << std::endl;
    return 2;
}